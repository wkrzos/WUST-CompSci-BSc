"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.OlxApiResponseSchema = exports.DatumSchema = exports.CategorySchema = exports.ContactSchema = exports.DeliverySchema = exports.RockSchema = exports.LocationSchema = exports.CitySchema = exports.DistrictSchema = exports.MapSchema = exports.ParamSchema = exports.ValueSchema = exports.PartnerSchema = exports.PhotoSchema = exports.PromotionSchema = exports.SafedealSchema = exports.ShopSchema = exports.UserSchema = exports.LinksSchema = exports.FirstSchema = exports.MetadataSchema = exports.AdvertsSchema = exports.ConfigSchema = exports.TargetingSchema = exports.SourceSchema = exports.SocialNetworkAccountTypeSchema = exports.CompanyNameSchema = exports.DatumStatusSchema = exports.SafedealStatusSchema = exports.CodeSchema = exports.ValueTypeSchema = exports.CurrencySchema = exports.ParamTypeSchema = exports.ParamNameSchema = exports.OfferTypeSchema = exports.NormalizedNameSchema = exports.CityNameSchema = exports.KeySchema = exports.ModeSchema = exports.CategoryTypeSchema = void 0;
const z = __importStar(require("zod"));
exports.CategoryTypeSchema = z.string();
exports.ModeSchema = z.string();
exports.KeySchema = z.enum([
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
exports.CityNameSchema = z.string();
exports.NormalizedNameSchema = z.string();
exports.OfferTypeSchema = z.enum(["offer"]);
exports.ParamNameSchema = z.union([
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
exports.ParamTypeSchema = z.enum(["input", "price", "select"]);
exports.CurrencySchema = z.enum(["PLN"]);
exports.ValueTypeSchema = z.enum(["arranged", "price"]);
exports.CodeSchema = z.string();
exports.SafedealStatusSchema = z.enum(["unactive"]);
exports.DatumStatusSchema = z.enum([
    "active",
    "removed_by_user",
    "disabled",
    "removed_by_moderator",
]);
exports.CompanyNameSchema = z.string();
exports.SocialNetworkAccountTypeSchema = z.string();
exports.SourceSchema = z.object({
    promoted: z.array(z.number()),
    organic: z.array(z.number()),
});
exports.TargetingSchema = z.object({
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
    region: exports.NormalizedNameSchema,
    subregion: exports.NormalizedNameSchema,
    city_id: z.string(),
    city: exports.NormalizedNameSchema,
    search_engine_input: z.string(),
    page: z.string(),
    segment: z.array(z.any()),
    app_version: z.string(),
});
exports.ConfigSchema = z.object({
    targeting: exports.TargetingSchema,
});
exports.AdvertsSchema = z.object({
    places: z.null(),
    config: exports.ConfigSchema,
});
exports.MetadataSchema = z.object({
    total_elements: z.number(),
    visible_total_count: z.number(),
    promoted: z.array(z.number()),
    search_id: z.string(),
    adverts: exports.AdvertsSchema,
    source: exports.SourceSchema,
});
exports.FirstSchema = z.object({
    href: z.string(),
});
exports.LinksSchema = z.object({
    self: exports.FirstSchema,
    previous: exports.FirstSchema,
    next: exports.FirstSchema,
    first: exports.FirstSchema,
});
exports.UserSchema = z.object({
    id: z.number(),
    created: z.string(),
    other_ads_enabled: z.boolean(),
    name: z.string(),
    logo: z.union([z.null(), z.string()]),
    photo: z.union([z.null(), z.string()]),
    banner_mobile: z.string(),
    banner_desktop: z.string(),
    company_name: exports.CompanyNameSchema,
    about: z.string(),
    b2c_business_page: z.boolean(),
    is_online: z.boolean(),
    last_seen: z.string(),
    seller_type: z.null(),
    uuid: z.string(),
});
exports.ShopSchema = z.object({
    subdomain: z.union([z.null(), z.string()]),
});
exports.SafedealSchema = z.object({
    weight: z.number(),
    weight_grams: z.number(),
    status: exports.SafedealStatusSchema,
    safedeal_blocked: z.boolean(),
    allowed_quantity: z.array(z.any()),
});
exports.PromotionSchema = z.object({
    highlighted: z.boolean(),
    urgent: z.boolean(),
    top_ad: z.boolean(),
    options: z.array(z.string()),
    b2c_ad_page: z.boolean(),
    premium_ad_page: z.boolean(),
});
exports.PhotoSchema = z.object({
    id: z.number(),
    filename: z.string(),
    rotation: z.number(),
    width: z.number(),
    height: z.number(),
    link: z.string(),
});
exports.PartnerSchema = z.object({
    code: exports.CodeSchema,
});
exports.ValueSchema = z.object({
    key: z.union([z.null(), z.string()]).optional(),
    label: z.string(),
    value: z.union([z.number(), z.null()]).optional(),
    type: z.union([exports.ValueTypeSchema, z.null()]).optional(),
    arranged: z.union([z.boolean(), z.null()]).optional(),
    budget: z.union([z.boolean(), z.null()]).optional(),
    currency: z.union([exports.CurrencySchema, z.null()]).optional(),
    negotiable: z.union([z.boolean(), z.null()]).optional(),
    converted_value: z.null().optional(),
    previous_value: z.union([z.number(), z.null()]).optional(),
    converted_previous_value: z.null().optional(),
    converted_currency: z.null().optional(),
});
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
        currency: z.union([exports.CurrencySchema, z.null()]).optional(),
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
exports.ParamSchema = z.discriminatedUnion("key", [
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
exports.MapSchema = z.object({
    zoom: z.number(),
    lat: z.number(),
    lon: z.number(),
    radius: z.number(),
    show_detailed: z.boolean(),
});
exports.DistrictSchema = z.object({
    id: z.number(),
    name: z.string(),
});
exports.CitySchema = z.object({
    id: z.number(),
    name: exports.CityNameSchema,
    normalized_name: exports.NormalizedNameSchema,
});
exports.LocationSchema = z.object({
    city: exports.CitySchema,
    district: z.union([exports.DistrictSchema, z.null()]).optional(),
    region: exports.CitySchema,
});
exports.RockSchema = z.object({
    offer_id: z.null(),
    active: z.boolean(),
    mode: exports.ModeSchema,
});
exports.DeliverySchema = z.object({
    rock: exports.RockSchema,
});
exports.ContactSchema = z.object({
    name: z.string(),
    phone: z.boolean(),
    chat: z.boolean(),
    negotiation: z.boolean(),
    courier: z.boolean(),
});
exports.CategorySchema = z.object({
    id: z.number(),
    type: exports.CategoryTypeSchema,
});
exports.DatumSchema = z.object({
    id: z.number(),
    url: z.string(),
    title: z.string(),
    last_refresh_time: z.string(),
    created_time: z.string(),
    valid_to_time: z.string(),
    pushup_time: z.union([z.null(), z.string()]),
    description: z.string(),
    params: z.array(exports.ParamSchema),
    key_params: z.array(exports.KeySchema),
    business: z.boolean(),
    user: exports.UserSchema,
    status: exports.DatumStatusSchema,
    contact: exports.ContactSchema,
    map: exports.MapSchema,
    location: exports.LocationSchema,
    photos: z.array(exports.PhotoSchema),
    category: exports.CategorySchema,
    offer_type: exports.OfferTypeSchema,
    external_url: z.union([z.null(), z.string()]).optional(),
});
exports.OlxApiResponseSchema = z.object({
    data: z.array(exports.DatumSchema),
});
