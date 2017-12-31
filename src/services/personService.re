open Faker;

open RandomJs;

open Uuid;

type person = {
  id: string,
  firstName: string,
  lastName: string,
  email: string,
  age: int,
  gender: string
};

let personDecoder = json =>
  Json.Decode.{
    id: json |> field("id", string),
    firstName: json |> field("firstName", string),
    lastName: json |> field("lastName", string),
    email: json |> field("email", string),
    age: json |> field("age", int),
    gender: json |> field("gender", string)
  };

let createPerson = () => {
  id: uuid(),
  firstName: faker##name##firstName(),
  lastName: faker##name##lastName(),
  email: faker##internet##email(),
  age: random |> Random.integer(17, 80),
  gender: random |> Random.pick([|"m", "f"|])
};

let getPersons = () =>
  Js.Promise.(
    Axios.get("http://localhost:8889/person")
    |> then_(response =>
         response##data |> Json.Decode.array(personDecoder) |> resolve
       )
  );