let make = _ => {
  let v = Vec.make();
  Js.log(0 == Vec.length(v));
  Js.log(Vec.default_growth_rate == Vec.growth_rate(v));

  let v = Vec.make(~growth_rate=3., ());
  Js.log(3. == Vec.growth_rate(v));
};

let assert_ = (a: 'a, b: int) => {
  Js.log2(a, b);
};
let assert_string = (a: string, b: bool) => {
  Js.log2(a, b);
};
let assert_bool = (a: bool, b: bool) => {
  Js.log2(a, b);
};
let assert_list = (a: list('a), b: list('a)) => {
  Js.log2(a, b);
};
let assert_unit = (_, a: unit => unit) => {
  Js.log2("assert_unit", a);
};
let assert_option = (a: option('a), b: option(int)) => {
  Js.log2(a, b);
};
let assert_array = (a: array('a), b: array(int)) => {
  Js.log2(a, b);
};
// let assert_raises = (~msg:string, exn,b:bool, unit =>(Vec.t('a, [> `R ]), int))=>(Vec.t('a, [> `R ]), int) => 'a => {Js.log2(msg, b)};
let assert_int_bool = (a: int, b: int) => {
  Js.log2(a, b);
};
let make = _ => {
  let v = Vec.make();
  assert_(0, Vec.length(v));
  assert_(Vec.default_growth_rate, Vec.growth_rate(v) |> int_of_float);

  let v = Vec.make(~growth_rate=3., ());
  assert_(3. == Vec.growth_rate(v));
};
let capacity = _ => {
  let v = Vec.make();

  Vec.ensure_capacity(20, v);
  assert_string("ensure_capacity", Vec.capacity(v) >= 20);

  Vec.reserve(30, v);
  assert_string("reserve", Vec.capacity(v) >= 50);

  Vec.push(2, v);
  Vec.shrink_to_fit(v);
  assert_(1, Vec.capacity(v));
};

let get_set = _ => {
  let v = Vec.make(~capacity=8, ());

  // assert_raises(~msg="get_exn", Invalid_argument("Index out of range"), () =>
  //   Vec.get_exn(v, 0)
  // );

  // assert_raises(~msg="set_exn", Invalid_argument("Index out of range"), () =>
  //   Vec.set_exn(v, 0, 0)
  // );

  assert_option(None, Vec.get(v, 0));
  assert_bool(false, Vec.set(v, 0, 0));

  Vec.push(1, v);

  // assert_unit((), Vec.set_exn(v, 0, 2));
  assert_(2, Vec.get_exn(v, 0));

  assert_bool(true, Vec.set(v, 0, 3));
  assert_option(Some(3), Vec.get(v, 0));
};

let push_pop = _ => {
  let v = Vec.make();

  Vec.push(1, v);
  assert_(1, Vec.length(v));

  Vec.push(3, v);
  assert_(2, Vec.length(v));

  assert_option(Some(3), Vec.pop(v));
  assert_option(Some(1), Vec.pop(v));
  assert_option(None, Vec.pop(v));
};

let map = _ => {
  let v = Vec.iota(0, 4);

  let v' = Vec.map(succ, v);
  assert_list([1, 2, 3, 4, 5], Vec.to_list(v'));

  Vec.map_in_place(succ, v');
  assert_list([2, 3, 4, 5, 6], Vec.to_list(v'));

  let v'' = Vec.mapi((i, _) => i, v');
  assert_list([0, 1, 2, 3, 4], Vec.to_list(v''));
};

let iter = _ => {
  let v = Vec.iota(0, 5);
  let expected = List.fold_left((+), 0, [0, 1, 2, 3, 4, 5]);
  let actual = ref(0);

  Vec.iter(i => actual := actual^ + i, v);
  assert_(expected, actual^);

  let actual = ref(true);
  Vec.iteri((i, a) => actual := actual^ && i == a, v);
  assert_string("iteri", actual^);
};

let cartesian_product = _ => {
  let a = Vec.of_list([1, 2, 3]);
  let b = Vec.of_list([10, 20, 30]);
  let expected = [
    (1, 10),
    (1, 20),
    (1, 30),
    (2, 10),
    (2, 20),
    (2, 30),
    (3, 10),
    (3, 20),
    (3, 30),
  ];

  assert_list(expected, Vec.to_list @@ Vec.cartesian_product(a, b));
};

let monad_ops = _ => {
  let list = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
  let a = Vec.map(Vec.of_list) @@ Vec.of_list(list);
  assert_list(List.flatten(list), Vec.to_list @@ Vec.flatten(a));

  let expected = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4];
  let f = i => Vec.of_list([i, i, i]);
  let a = Vec.iota(1, 4);
  assert_list(expected, Vec.to_list @@ Vec.flat_map(f, a));
};

let filter = _ => {
  let v = Vec.iota(0, 10);
  let even = i => i mod 2 == 0;
  assert_list([0, 2, 4, 6, 8, 10], Vec.to_list @@ Vec.filter(even, v));
  assert_(Vec.length(v), Vec.length @@ Vec.filteri((==), v));

  Vec.filter_in_place(even, v);
  assert_(6, Vec.length(v));
};

let conversions = _ => {
  let l = [1, 2, 3, 4, 5];
  let v = Vec.of_list(l);
  assert_list(l, Vec.to_list(v));

  Vec.reserve(100, v);
  let a = Vec.to_array(v);
  assert_array([|1, 2, 3, 4, 5|], a);
  assert_(5, Array.length(a));
};

let rev = _ => {
  let l = [1, 2, 3, 4, 5, 6];
  let v = Vec.of_list(l);
  assert_list(List.rev(l), Vec.to_list @@ Vec.rev(v));

  Vec.rev_in_place(v);
  assert_list(List.rev(l), Vec.to_list(v));
};

let append = _ => {
  let l1 = [1, 2, 3, 4, 5];
  let l2 = [6, 7, 8, 9, 10];

  let v = Vec.of_list(l1);
  let v2 = Vec.of_list(l2);

  Vec.append(v, v2);
  assert_list(l1 @ l2, Vec.to_list(v));
  assert_(10, Vec.length(v));
};

let exists = _ => {
  let v = Vec.of_list([1, 2, 3, 4, 5]);
  assert_string("exists", Vec.exists((==)(4), v));
  assert_string("not exists", (!) @@ Vec.exists((==)(6), v));
  assert_string("exists empty", (!) @@ Vec.exists(_ => true) @@ Vec.make());
};

let for_all = _ => {
  let v = Vec.iota(5, 1);
  assert_string("for_all", Vec.for_all((<=)(1), v));
  assert_string("not for_all", (!) @@ Vec.for_all((<=)(3), v));
  assert_string("for_all empty", Vec.for_all(_ => false) @@ Vec.make());
};

let mem = _ => {
  let v = Vec.iota(1, 100);
  assert_string("mem", Vec.mem(95, v));
  assert_string("mem not", (!) @@ Vec.mem(101, v));

  let a = [|1, 2|];
  let b = [|1, 2|];
  let v = Vec.of_list([[|1, 2|], a, [|1, 2|]]);
  assert_string("memq", Vec.memq(a, v));
  assert_string("memq", (!) @@ Vec.memq(b, v));
};

let folds = _ => {
  let v = Vec.iota(1, 100);
  let l = Vec.to_list(v);

  let expected = List.fold_left((+), 0, l);
  let actual = Vec.fold_left((+), 0, v);
  assert_(expected, actual);

  let expected = List.fold_right(Int.mul, l, 1);
  let actual = Vec.fold_right(Int.mul, v, 1);
  assert_(expected, actual);

  let z = (-50);
  let empty = Vec.make();
  assert_(z, Vec.fold_left((+), z, empty));
  assert_(z, Vec.fold_right((+), empty, z));
};

let zip = _ => {
  let a = Vec.iota(1, 3);
  let b = Vec.iota(4, 6);

  let expected = [(1, 4), (2, 5), (3, 6)];
  assert_list(expected, Vec.to_list @@ Vec.zip(a, b));

  let expected = [5, 7, 9];
  assert_list(expected, Vec.to_list @@ Vec.zip_with((+), a, b));
};

let equal = _ => {
  assert_string("equal empty") @@ Vec.equal(Vec.make(), Vec.make());

  let a = Vec.of_list([1, 2, 3, 4, 5]);
  let b = Vec.iota(1, 5);

  assert_string("equal non-empty", Vec.equal(a, b));

  Vec.reserve(10, a);
  assert_string("equal diff capacity", Vec.equal(a, b));

  Vec.push(6, a);
  assert_string("equal diff length", (!) @@ Vec.equal(a, b));
};

let compare = _ => {
  assert_(0) @@ Vec.compare(Vec.make(), Vec.make());

  let a = Vec.of_list(['a', 'b', 'c']);
  let b = Vec.of_list(['a', 'b', 'd']);

  assert_(0, Vec.compare(a, a));
  assert_(-1, Vec.compare(a, b));
  assert_(1, Vec.compare(b, a));

  let a = Vec.of_list(['a', 'b', 'c']);
  let b = Vec.of_list(['a', 'b', 'c', 'd', 'e']);
  assert_(-1, Vec.compare(a, b));

  let a = Vec.of_list(['a', 'b', 'c', 'd']);
  let b = Vec.of_list(['e', 'f']);
  assert_(-1, Vec.compare(a, b));
};
let assert_: (string, string, unit) => unit =
  (a: string, b: string) => {
    Js.log2(a == b);
  };
let pretty_print2 = _ => {
  let pp = Vec.pretty_print(Int.to_string);

  assert_("[]", pp @@ Vec.make(), ());
  assert_("[2]", pp @@ Vec.singleton(2), ());
  assert_("[1; 2; 3; 4; 5]", pp @@ Vec.iota(1, 5), ());

  let pp = Vec.pretty_print(s => s);
  assert_("[abc; def]", pp @@ Vec.of_list(["abc", "def"]), ());

  let pp = Vec.pretty_print(s => Int.to_string @@ String.length(s));
  assert_("[3; 4; 5]", pp @@ Vec.of_list(["aaa", "abcd", "abcde"]));
};
let pretty_print = _ => {
  let pp = Vec.pretty_print(Int.to_string);

  Js.log("pretty_print");
  Js.log("[]" == pp @@ Vec.make());
  Js.log("[2]" == pp @@ Vec.singleton(2));
  Js.log("[1; 2; 3; 4; 5]" == pp @@ Vec.iota(1, 5));

  let pp = Vec.pretty_print(s => s);
  Js.log("[abc; def]" == pp @@ Vec.of_list(["abc", "def"]));

  let pp = Vec.pretty_print(s => Int.to_string @@ String.length(s));
  Js.log("[3; 4; 5]" == pp @@ Vec.of_list(["aaa", "abcd", "abcde"]));
};

let test_suite = (
  "Tests",
  [
    Js.log2("make", make()),
    Js.log2("capacity", capacity()),
    Js.log2("get_set", get_set()),
    Js.log2("push_pop", push_pop()),
    Js.log2("map", map()),
    Js.log2("iter", iter()),
    Js.log2("cartesian_product", cartesian_product()),
    Js.log2("monad_ops", monad_ops()),
    Js.log2("filter", filter()),
    Js.log2("conversions", conversions()),
    Js.log2("rev", rev()),
    Js.log2("append", append()),
    Js.log2("exists", exists()),
    Js.log2("for_all", for_all()),
    Js.log2("mem", mem()),
    Js.log2("folds", folds()),
    Js.log2("zip", zip()),
    Js.log2("equal", equal()),
    Js.log2("compare", compare()),
    Js.log2("pretty_print", pretty_print()),
    Js.log2("pretty_print2", pretty_print2()),
  ],
);

// let () = run_test_tt_main(test_suite);
test_suite;
