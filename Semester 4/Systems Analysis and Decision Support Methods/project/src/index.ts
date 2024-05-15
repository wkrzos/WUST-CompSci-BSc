import { logger } from "logger";
import { z } from "zod";
import fs from "fs";
import { createObjectCsvWriter } from "csv-writer";

import { fetchData } from "./fetchData";
import { CitiesResponseSchema } from "./cities_schema";
import { categories, regions } from "./constants";
import { OlxApiResponseSchema } from "./response_schema";

const baseApi = "https://www.olx.pl/api/v1";
const apiUrl = "https://www.olx.pl/api/v1/offers";

const SearchParams = z
  .object({
    offset: z.number(),
    limit: z.number().min(0).max(50),
    category_id: z.number(),
    query: z.string().optional(),
    sort_by: z.literal("created_at:desc").optional(),
    "filter_float_price:to": z.number().optional(),
    "filter_float_price:from": z.number().optional(),
    "filter_float_m:from": z.number().optional(),
    "filter_float_m:to": z.number().optional(),
    rooms: z.array(z.enum(["one", "two", "three"])).optional(),
    "filter_enum_rooms[0]": z.enum(["one", "two", "three"]).optional(),
    "filter_enum_rooms[1]": z.enum(["one", "two", "three"]).optional(),
    "filter_enum_rooms[2]": z.enum(["one", "two", "three"]).optional(),
    "filter_enum_roomsize[0]": z.enum(["one", "two", "three"]).optional(),
    "filter_enum_roomsize[1]": z.enum(["one", "two", "three"]).optional(),
    "filter_enum_roomsize[2]": z.enum(["one", "two", "three"]).optional(),
  })
  .transform((data) => {
    if (data.category_id === categories.Rooms) {
      data.rooms?.forEach((room, i) => {
        data[`filter_enum_roomsize[${i.toString() as "0"}]`] = room;
      });

      delete data.rooms;
      return data;
    }

    if (data.category_id === categories.Apartments) {
      data.rooms?.forEach((room, i) => {
        data[`filter_enum_rooms[${i.toString() as "0"}]`] = room;
      });

      delete data.rooms;
      return data;
    }

    return data;
  });

export const apiClient = {
  offers: {
    list: async (options) => {
      const optionsToString = Object.fromEntries(
        Object.entries(options).map(([key, value]) => [key, value.toString()])
      );

      const urlSearchParams = new URLSearchParams(optionsToString);
      const url = `${apiUrl}/?${urlSearchParams}`;
      const res = await fetchData(url);

      const offers = OlxApiResponseSchema.safeParse(JSON.parse(res));

      if (!offers.success) {
        logger.error(offers.error);
        logger.error(JSON.stringify(offers));
      }

      return offers.success
        ? offers.data
        : {
            data: [],
          };
    },
  },
  cities: {
    list: async (regionId, options) => {
      const url = `${baseApi}/geo-encoder/regions/${regionId}/cities/?limit=${options?.limit ?? 300}`;
      const res = await fetchData(url);
      const parsedCities = CitiesResponseSchema.parse(JSON.parse(res));
      return parsedCities;
    },
  },
};

const writeOffersToCsv = async (offers) => {
  const csvWriter = createObjectCsvWriter({
    path: 'offers.csv',
    header: [
      { id: 'id', title: 'ID' },
      { id: 'title', title: 'Title' },
      { id: 'price', title: 'Price' },
      { id: 'description', title: 'Description' },
      { id: 'created_at', title: 'Created At' },
    ],
  });

  const records = offers.data.map((offer) => ({
    id: offer.id,
    title: offer.title,
    price: offer.params?.price?.value,
    description: offer.description,
    created_at: offer.created_at,
  }));

  await csvWriter.writeRecords(records);
  console.log('The CSV file was written successfully');
};

// Example usage:
const fetchAndSaveOffers = async () => {
  const searchParams = {
    offset: 0,
    limit: 10,
    category_id: categories.Apartments,
  };

  const offers = await apiClient.offers.list(searchParams);
  await writeOffersToCsv(offers);
};

fetchAndSaveOffers();
