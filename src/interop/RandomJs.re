module Type = {
  type randomJs;
  type randomEngine = {. [@bs.meth] "autoSeed": unit => randomEngine};
  type engines = {. [@bs.meth] "mt19937": unit => randomEngine};
};

module Random = {
  [@bs.send.pipe : Type.randomJs] external integer : (int, int) => int = "";
  [@bs.send.pipe : Type.randomJs] external pick : array('a) => 'a = "";
};

[@bs.module] [@bs.new]
external randomJs : Type.randomEngine => Type.randomJs = "random-js";

[@bs.module "random-js"] external engines : Type.engines = "";

let random = engines##mt19937()##autoSeed() |> randomJs;