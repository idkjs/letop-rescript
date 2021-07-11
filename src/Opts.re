let (let.opt) = (x, f) =>
  switch (x) {
  | None => None
  | Some(x) => f(x)
  };
let (and.opt) = (a, b) =>
  switch (a, b) {
  | (Some(a), Some(b)) => Some((a, b))
  | _ => None
  };
let z = (a,b)=> {
  let.opt a = a
  and.opt b = b;
  Some(a + b);
};

