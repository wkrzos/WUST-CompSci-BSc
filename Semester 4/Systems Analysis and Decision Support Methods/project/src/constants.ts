export const regions = {
    Mazowieckie: 2,
    Śląskie: 6,
    Dolnośląskie: 3,
    Małopolskie: 4,
    Wielkopolskie: 1,
    Łódzkie: 7,
    Pomorskie: 5,
    "Kujawsko-pomorskie": 15,
    Zachodniopomorskie: 11,
    Lubelskie: 8,
    "Warmińsko-mazurskie": 14,
    Podkarpackie: 17,
    Podlaskie: 18,
    Lubuskie: 9,
    Świętokrzyskie: 13,
    Opolskie: 12,
  };
  const ApartmentsId = 15 as const;
  const RoomsId = 11 as const;
  export const categories = {
    Apartments: ApartmentsId,
    Rooms: RoomsId,
  } as const;