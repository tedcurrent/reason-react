module Type = {
  type name = {
    .
    [@bs.meth] "firstName": unit => string,
    [@bs.meth] "lastName": unit => string
  };
  type internet = {. [@bs.meth] "email": unit => string};
  type faker = {
    .
    [@bs.meth] "name": name,
    [@bs.meth] "internet": internet
  };
};

[@bs.module] external faker : Type.faker = "";