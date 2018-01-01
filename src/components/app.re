open PersonService;

[%bs.raw {|require('./app.css')|}];

type state = {persons: option(list(person))};

type action =
  | Add(person)
  | Delete(string)
  | Update(list(person));

let add = person => Add(person);

let delete = id => Delete(id);

let update = persons => Update(persons);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {persons: None},
  reducer: (action, state) =>
    switch action {
    | Add(person) =>
      ReasonReact.Update({
        persons:
          switch state.persons {
          | None => Some([person])
          | Some(persons) => Some([person, ...persons])
          }
      })
    | Delete(id) =>
      switch state.persons {
      | None => ReasonReact.NoUpdate
      | Some(persons) =>
        ReasonReact.Update({
          persons: Some(persons |> List.filter(person => person.id !== id))
        })
      }
    | Update(persons) => ReasonReact.Update({persons: Some(persons)})
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
  render: self => {
    let {persons} = self.state;
    let personList =
      switch persons {
      | None => ReasonReact.stringToElement("Loading...")
      | Some([]) =>
        ReasonReact.stringToElement("You have fired everyone! Good job.")
      | Some(persons) =>
        <PersonList persons deletePerson=(self.reduce(delete)) />
      };
    <div className="App">
      <div className="App-header">
        <h1> (ReasonReact.stringToElement("Firing simulator 2018!")) </h1>
        <h2> (ReasonReact.stringToElement("Add person to fire")) </h2>
        <CreatePersonForm onSubmit=(self.reduce(add)) />
      </div>
      <div className="App-intro"> personList </div>
    </div>;
  }
};