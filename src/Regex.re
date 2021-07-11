Js.log("Hello, Reason!")
/* Tests for Re higher-level functions */
// open OUnit;

module String = {
  [@ocaml.warning "-32-3"];
  let capitalize_ascii = String.capitalize;
  let uncapitalize_ascii = String.uncapitalize;
  let uppercase_ascii = String.uppercase;
  let lowercase_ascii = String.lowercase;
  include String;
};

let pp_str = (x) => x;

let quote = Printf.sprintf("'%s'");

let pp_list = (l) => l |> List.map(quote) |> String.concat(", ") |> Printf.sprintf("[ %s ]");

let re_whitespace = Re.Posix.compile_pat("[\t ]+");

let re_empty = Re.Posix.compile_pat("");

// let re_eol = Re.compile(Re.eol);

// let re_bow = Re.compile(Re.bow);

// let re_eow = Re.compile(Re.eow);
