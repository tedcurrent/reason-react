open Jest;

open PersonService;

describe("personService", () =>
  describe("createPreson", () =>
    test("should return person with age less than 81", () =>
      Expect.(expect(createPerson().age) |> toBeLessThan(81))
    )
  )
);