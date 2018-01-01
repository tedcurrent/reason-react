open PersonService;

let component = ReasonReact.statelessComponent("PersonList");

let make = (~persons, ~deletePerson, _children) => {
  ...component,
  render: _self => {
    let personList =
      persons
      |> List.sort((a, b) => Pervasives.compare(a.firstName, b.firstName))
      |> List.sort((a, b) => Pervasives.compare(a.lastName, b.lastName))
      |> List.map(person => <Person key=person.id person deletePerson />)
      |> Array.of_list;
    <div> (ReasonReact.arrayToElement(personList)) </div>;
  }
};