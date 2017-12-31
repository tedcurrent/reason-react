let component = ReasonReact.statelessComponent("Person");

let make = (~person: PersonService.person, ~deletePerson, _children) => {
  ...component,
  render: _self =>
    <div>
      <div>
        <strong>
          (ReasonReact.stringToElement(person.lastName ++ " "))
        </strong>
        (ReasonReact.stringToElement(person.firstName))
      </div>
      (ReasonReact.stringToElement(string_of_int(person.age) ++ " years, "))
      (ReasonReact.stringToElement(person.gender))
      <button onClick=(_event => deletePerson(person.id))>
        (ReasonReact.stringToElement("fire"))
      </button>
      <div />
    </div>
};