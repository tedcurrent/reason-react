open PersonService;

[%bs.raw {|require('./app.css')|}];

type action =
  | Delete(string)
  | Update(list(PersonService.person));

let delete = id => Delete(id);

let update = persons => Update(persons);

type state = {persons: list(person)};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {persons: []},
  reducer: (action, state) =>
    switch action {
    | Delete(id) =>
      ReasonReact.Update({
        persons: state.persons |> List.filter(person => person.id !== id)
      })
    | Update(persons) => ReasonReact.Update({persons: persons})
    },
  didMount: self => {
    Js.Promise.(
      getPersons()
      |> then_(data =>
           self.reduce((_) => update(data |> Array.to_list), ()) |> resolve
         )
    )
    |> ignore;
    ReasonReact.NoUpdate;
  },
  render: self =>
    <div className="App">
      <div className="App-header">
        <h1> (ReasonReact.stringToElement("Awesome app!")) </h1>
      </div>
      <div className="App-intro">
        <PersonList
          persons=self.state.persons
          deletePerson=(self.reduce(delete))
        />
      </div>
    </div>
};