let (let.force) = (v, fin) =>
  switch (v) {
  | Error(e) => failwith("Force unwrapping an Error'd Result")
  | Belt.Result.Ok(v) => fin(v)
  };
let z = {
  let.force a = Belt.Result.Ok("1");
  Some(a);
};
Js.log(z)
