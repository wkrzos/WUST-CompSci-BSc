import * as z from "zod";

export const CategoryTypeSchema = z.string();
export type CategoryType = z.infer<typeof CategoryTypeSchema>;

export const ModeSchema = z.string();
export type Mode = z.infer<typeof ModeSchema>;

export const KeySchema = z.enum([
  "builttype",
  "floor_select",
  "furniture",
  "m",
  "price",
  "rent",
  "rooms",
  "roomsize",
  "preferences",
]);
export type Key = z.infer<typeof KeySchema>;

export const CityNameSchema = z.string();
export type CityName = z.infer<typeof CityNameSchema>;

export const NormalizedNameSchema = z.string();
export type NormalizedName = z.infer<typeof NormalizedNameSchema>;

export const OfferTypeSchema = z.enum(["offer"]);
export type OfferType = z.infer<typeof OfferTypeSchema>;

export const ParamNameSchema = z.union([
  z.literal("Cena"),
  z.literal("Czynsz (dodatkowo)"),
  z.literal("Liczba pokoi"),
  z.literal("Powierzchnia"),
  z.literal("Poziom"),
  z.literal("Rodzaj zabudowy"),
  z.literal("Umeblowane"),
  z.literal("Preferowani"),
  z.literal("Rodzaj pokoju"),
  z.string(),
]);
export type ParamName = z.infer<typeof ParamNameSchema>;

export const ParamTypeSchema = z.enum(["input", "price", "select"]);
export type ParamType = z.infer<typeof ParamTypeSchema>;

export const CurrencySchema = z.enum(["PLN"]);
export type Currency = z.infer<typeof CurrencySchema>;

export const ValueTypeSchema = z.enum(["arranged", "price"]);
export type ValueType = z.infer<typeof ValueTypeSchema>;

export const CodeSchema = z.string();
export type Code = z.infer<typeof CodeSchema>;

export const SafedealStatusSchema = z.enum(["unactive"]);
export type SafedealStatus = z.infer<typeof SafedealStatusSchema>;

export const DatumStatusSchema = z.enum([
  "active",
  "removed_by_user",
  "disabled",
  "removed_by_moderator",
]);
export type DatumStatus = z.infer<typeof DatumStatusSchema>;

export const CompanyNameSchema = z.string();
export type CompanyName = z.infer<typeof CompanyNameSchema>;

export const SocialNetworkAccountTypeSchema = z.string();
export type SocialNetworkAccountType = z.infer<
  typeof SocialNetworkAccountTypeSchema
>;

export const SourceSchema = z.object({
  promoted: z.array(z.number()),
  organic: z.array(z.number()),
});
export type Source = z.infer<typeof SourceSchema>;

export const TargetingSchema = z.object({
  env: z.string(),
  lang: z.string(),
  account: z.string(),
  dfp_user_id: z.string(),
  user_status: z.string(),
  cat_l0_id: z.string(),
  cat_l1_id: z.string(),
  cat_l2_id: z.string(),
  cat_l0: z.string(),
  cat_l0_path: z.string(),
  cat_l1: z.string(),
  cat_l1_path: z.string(),
  cat_l2: z.string(),
  cat_l2_path: z.string(),
  cat_l0_name: z.string(),
  cat_l1_name: z.string(),
  cat_l2_name: z.string(),
  cat_id: z.string(),
  private_business: z.string(),
  offer_seek: z.string(),
  view: z.string(),
  region_id: z.string(),
  region: NormalizedNameSchema,
  subregion: NormalizedNameSchema,
  city_id: z.string(),
  city: NormalizedNameSchema,
  search_engine_input: z.string(),
  page: z.string(),
  segment: z.array(z.any()),
  app_version: z.string(),
});
export type Targeting = z.infer<typeof TargetingSchema>;

export const ConfigSchema = z.object({
  targeting: TargetingSchema,
});
export type Config = z.infer<typeof ConfigSchema>;

export const AdvertsSchema = z.object({
  places: z.null(),
  config: ConfigSchema,
});
export type Adverts = z.infer<typeof AdvertsSchema>;

export const MetadataSchema = z.object({
  total_elements: z.number(),
  visible_total_count: z.number(),
  promoted: z.array(z.number()),
  search_id: z.string(),
  adverts: AdvertsSchema,
  source: SourceSchema,
});
export type Metadata = z.infer<typeof MetadataSchema>;

export const FirstSchema = z.object({
  href: z.string(),
});
export type First = z.infer<typeof FirstSchema>;

export const LinksSchema = z.object({
  self: FirstSchema,
  previous: FirstSchema,
  next: FirstSchema,
  first: FirstSchema,
});
export type Links = z.infer<typeof LinksSchema>;

export const UserSchema = z.object({
  id: z.number(),
  created: z.string(),
  other_ads_enabled: z.boolean(),
  name: z.string(),
  logo: z.union([z.null(), z.string()]),
  photo: z.union([z.null(), z.string()]),
  banner_mobile: z.string(),
  banner_desktop: z.string(),
  company_name: CompanyNameSchema,
  about: z.string(),
  b2c_business_page: z.boolean(),
  is_online: z.boolean(),
  last_seen: z.string(),
  seller_type: z.null(),
  uuid: z.string(),
});
export type User = z.infer<typeof UserSchema>;

export const ShopSchema = z.object({
  subdomain: z.union([z.null(), z.string()]),
});
export type Shop = z.infer<typeof ShopSchema>;

export const SafedealSchema = z.object({
  weight: z.number(),
  weight_grams: z.number(),
  status: SafedealStatusSchema,
  safedeal_blocked: z.boolean(),
  allowed_quantity: z.array(z.any()),
});
export type Safedeal = z.infer<typeof SafedealSchema>;

export const PromotionSchema = z.object({
  highlighted: z.boolean(),
  urgent: z.boolean(),
  top_ad: z.boolean(),
  options: z.array(z.string()),
  b2c_ad_page: z.boolean(),
  premium_ad_page: z.boolean(),
});
export type Promotion = z.infer<typeof PromotionSchema>;

export const PhotoSchema = z.object({
  id: z.number(),
  filename: z.string(),
  rotation: z.number(),
  width: z.number(),
  height: z.number(),
  link: z.string(),
});
export type Photo = z.infer<typeof PhotoSchema>;

export const PartnerSchema = z.object({
  code: CodeSchema,
});
export type Partner = z.infer<typeof PartnerSchema>;

export const ValueSchema = z.object({
  key: z.union([z.null(), z.string()]).optional(),
  label: z.string(),
  value: z.union([z.number(), z.null()]).optional(),
  type: z.union([ValueTypeSchema, z.null()]).optional(),
  arranged: z.union([z.boolean(), z.null()]).optional(),
  budget: z.union([z.boolean(), z.null()]).optional(),
  currency: z.union([CurrencySchema, z.null()]).optional(),
  negotiable: z.union([z.boolean(), z.null()]).optional(),
  converted_value: z.null().optional(),
  previous_value: z.union([z.number(), z.null()]).optional(),
  converted_previous_value: z.null().optional(),
  converted_currency: z.null().optional(),
});
export type Value = z.infer<typeof ValueSchema>;

const AreaParam = z.object({
  key: z.literal("m"),
  name: z.string(),
  type: z.literal("input"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    value: z.union([z.number(), z.null()]).optional(),
  }),
});

const RentParam = z.object({
  key: z.literal("rent"),
  name: z.string(),
  type: z.literal("input"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

const PriceParam = z.object({
  key: z.literal("price"),
  name: z.string(),
  type: z.literal("price"),
  value: z.object({
    value: z.union([z.number(), z.null()]).optional(),
    currency: z.union([CurrencySchema, z.null()]).optional(),
    negotiable: z.union([z.boolean(), z.null()]).optional(),
    label: z.string(),
  }),
});

const FurnitureParam = z.object({
  key: z.literal("furniture"),
  name: z.string(),
  type: z.literal("select"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

const RoomsParam = z.object({
  key: z.literal("rooms"),
  name: z.string(),
  type: z.literal("select"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

const BuiltTypeParam = z.object({
  key: z.literal("builttype"),
  name: z.string(),
  type: z.literal("select"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

const FloorParam = z.object({
  key: z.literal("floor_select"),
  name: z.string(),
  type: z.literal("select"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

const RoomSizeParam = z.object({
  key: z.literal("roomsize"),
  name: z.string(),
  type: z.literal("select"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

const PreferencesParam = z.object({
  key: z.literal("preferences"),
  name: z.string(),
  type: z.literal("select"),
  value: z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
  }),
});

export const ParamSchema = z.discriminatedUnion("key", [
  AreaParam,
  RentParam,
  PriceParam,
  FurnitureParam,
  RoomsParam,
  BuiltTypeParam,
  FloorParam,
  RoomSizeParam,
  PreferencesParam,
]);
export type Param = z.infer<typeof ParamSchema>;

export const MapSchema = z.object({
  zoom: z.number(),
  lat: z.number(),
  lon: z.number(),
  radius: z.number(),
  show_detailed: z.boolean(),
});
export type Map = z.infer<typeof MapSchema>;

export const DistrictSchema = z.object({
  id: z.number(),
  name: z.string(),
});
export type District = z.infer<typeof DistrictSchema>;

export const CitySchema = z.object({
  id: z.number(),
  name: CityNameSchema,
  normalized_name: NormalizedNameSchema,
});
export type City = z.infer<typeof CitySchema>;

export const LocationSchema = z.object({
  city: CitySchema,
  district: z.union([DistrictSchema, z.null()]).optional(),
  region: CitySchema,
});
export type Location = z.infer<typeof LocationSchema>;

export const RockSchema = z.object({
  offer_id: z.null(),
  active: z.boolean(),
  mode: ModeSchema,
});
export type Rock = z.infer<typeof RockSchema>;

export const DeliverySchema = z.object({
  rock: RockSchema,
});
export type Delivery = z.infer<typeof DeliverySchema>;

export const ContactSchema = z.object({
  name: z.string(),
  phone: z.boolean(),
  chat: z.boolean(),
  negotiation: z.boolean(),
  courier: z.boolean(),
});
export type Contact = z.infer<typeof ContactSchema>;

export const CategorySchema = z.object({
  id: z.number(),
  type: CategoryTypeSchema,
});
export type Category = z.infer<typeof CategorySchema>;

export const DatumSchema = z.object({
  id: z.number(),
  url: z.string(),
  title: z.string(),
  last_refresh_time: z.string(),
  created_time: z.string(),
  valid_to_time: z.string(),
  pushup_time: z.union([z.null(), z.string()]),
  description: z.string(),
  params: z.array(ParamSchema),
  key_params: z.array(KeySchema),
  business: z.boolean(),
  user: UserSchema,
  status: DatumStatusSchema,
  contact: ContactSchema,
  map: MapSchema,
  location: LocationSchema,
  photos: z.array(PhotoSchema),
  category: CategorySchema,
  offer_type: OfferTypeSchema,
  external_url: z.union([z.null(), z.string()]).optional(),
});
export type Datum = z.infer<typeof DatumSchema>;

export const OlxApiResponseSchema = z.object({
  data: z.array(DatumSchema),
});
export type OlxApiResponse = z.infer<typeof OlxApiResponseSchema>;