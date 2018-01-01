type state = {
  firstName: string,
  lastName: string
};

type inputField =
  | FirstName
  | LastName;

type action =
  | Update(inputField, string);

let update = (field, value) => Update(field, value);

let component = ReasonReact.reducerComponent("CreatePersonForm");

let make = (~onSubmit, _children) => {
  let change = (field, event) => {
    let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
    update(field, value);
  };
  let submit = (event, self) => {
    event |> ReactEventRe.Form.preventDefault;
    onSubmit({
      ...PersonService.createPerson(),
      firstName: self.ReasonReact.state.firstName,
      lastName: self.ReasonReact.state.lastName
    });
  };
  {
    ...component,
    initialState: () => {firstName: "", lastName: ""},
    reducer: (action, state) =>
      switch action {
      | Update(field, text) =>
        switch field {
        | FirstName => ReasonReact.Update({...state, firstName: text})
        | LastName => ReasonReact.Update({...state, lastName: text})
        }
      },
    render: self =>
      <form onSubmit=(self.handle(submit))>
        <input
          _type="text"
          value=self.state.firstName
          onChange=(self.reduce(change(FirstName)))
          placeholder="John"
        />
        <input
          _type="text"
          value=self.state.lastName
          onChange=(self.reduce(change(LastName)))
          placeholder="Doe"
        />
        <input _type="submit" />
      </form>
  };
};