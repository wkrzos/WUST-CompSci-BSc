"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.apiClient = void 0;
const logger_1 = require("logger");
const zod_1 = require("zod");
const csv_writer_1 = require("csv-writer");
const fetchData_1 = require("./fetchData");
const cities_schema_1 = require("./cities_schema");
const constants_1 = require("./constants");
const response_schema_1 = require("./response_schema");
const baseApi = "https://www.olx.pl/api/v1";
const apiUrl = "https://www.olx.pl/api/v1/offers";
const SearchParams = zod_1.z
    .object({
    offset: zod_1.z.number(),
    limit: zod_1.z.number().min(0).max(50),
    category_id: zod_1.z.number(),
    query: zod_1.z.string().optional(),
    sort_by: zod_1.z.literal("created_at:desc").optional(),
    "filter_float_price:to": zod_1.z.number().optional(),
    "filter_float_price:from": zod_1.z.number().optional(),
    "filter_float_m:from": zod_1.z.number().optional(),
    "filter_float_m:to": zod_1.z.number().optional(),
    rooms: zod_1.z.array(zod_1.z.enum(["one", "two", "three"])).optional(),
    "filter_enum_rooms[0]": zod_1.z.enum(["one", "two", "three"]).optional(),
    "filter_enum_rooms[1]": zod_1.z.enum(["one", "two", "three"]).optional(),
    "filter_enum_rooms[2]": zod_1.z.enum(["one", "two", "three"]).optional(),
    "filter_enum_roomsize[0]": zod_1.z.enum(["one", "two", "three"]).optional(),
    "filter_enum_roomsize[1]": zod_1.z.enum(["one", "two", "three"]).optional(),
    "filter_enum_roomsize[2]": zod_1.z.enum(["one", "two", "three"]).optional(),
})
    .transform((data) => {
    var _a, _b;
    if (data.category_id === constants_1.categories.Rooms) {
        (_a = data.rooms) === null || _a === void 0 ? void 0 : _a.forEach((room, i) => {
            data[`filter_enum_roomsize[${i.toString()}]`] = room;
        });
        delete data.rooms;
        return data;
    }
    if (data.category_id === constants_1.categories.Apartments) {
        (_b = data.rooms) === null || _b === void 0 ? void 0 : _b.forEach((room, i) => {
            data[`filter_enum_rooms[${i.toString()}]`] = room;
        });
        delete data.rooms;
        return data;
    }
    return data;
});
exports.apiClient = {
    offers: {
        list: (options) => __awaiter(void 0, void 0, void 0, function* () {
            const optionsToString = Object.fromEntries(Object.entries(options).map(([key, value]) => [key, value.toString()]));
            const urlSearchParams = new URLSearchParams(optionsToString);
            const url = `${apiUrl}/?${urlSearchParams}`;
            const res = yield (0, fetchData_1.fetchData)(url);
            const offers = response_schema_1.OlxApiResponseSchema.safeParse(JSON.parse(res));
            if (!offers.success) {
                logger_1.logger.error(offers.error);
                logger_1.logger.error(JSON.stringify(offers));
            }
            return offers.success
                ? offers.data
                : {
                    data: [],
                };
        }),
    },
    cities: {
        list: (regionId, options) => __awaiter(void 0, void 0, void 0, function* () {
            var _a;
            const url = `${baseApi}/geo-encoder/regions/${regionId}/cities/?limit=${(_a = options === null || options === void 0 ? void 0 : options.limit) !== null && _a !== void 0 ? _a : 300}`;
            const res = yield (0, fetchData_1.fetchData)(url);
            const parsedCities = cities_schema_1.CitiesResponseSchema.parse(JSON.parse(res));
            return parsedCities;
        }),
    },
};
const writeOffersToCsv = (offers) => __awaiter(void 0, void 0, void 0, function* () {
    const csvWriter = (0, csv_writer_1.createObjectCsvWriter)({
        path: 'offers.csv',
        header: [
            { id: 'id', title: 'ID' },
            { id: 'title', title: 'Title' },
            { id: 'price', title: 'Price' },
            { id: 'description', title: 'Description' },
            { id: 'created_at', title: 'Created At' },
        ],
    });
    const records = offers.data.map((offer) => {
        var _a, _b;
        return ({
            id: offer.id,
            title: offer.title,
            price: (_b = (_a = offer.params) === null || _a === void 0 ? void 0 : _a.price) === null || _b === void 0 ? void 0 : _b.value,
            description: offer.description,
            created_at: offer.created_at,
        });
    });
    yield csvWriter.writeRecords(records);
    console.log('The CSV file was written successfully');
});
// Example usage:
const fetchAndSaveOffers = () => __awaiter(void 0, void 0, void 0, function* () {
    const searchParams = {
        offset: 0,
        limit: 10,
        category_id: constants_1.categories.Apartments,
    };
    const offers = yield exports.apiClient.offers.list(searchParams);
    yield writeOffersToCsv(offers);
});
fetchAndSaveOffers();
