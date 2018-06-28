let where = (fn, arr) =>
  Belt.List.reduce(arr, List.nth(arr, 0), (a, b) => fn(a, b) ? a : b);

let min = arr => where((a, b) => a < b, arr);

let max = arr => where((a, b) => a > b, arr);

let rec repeatStringAux = (n, string, acc) =>
  if (n == 0) {
    acc;
  } else {
    repeatStringAux(n - 1, string, acc ++ string);
  };

let repeatString = (n, string) => repeatStringAux(n, string, "");

let rec splitToChunksAux = (size, str, acc) =>
  if (String.length(str) == 0) {
    acc;
  } else {
    let part = Js.String.slice(~from=0, ~to_=size, str);
    let rest = Js.String.sliceToEnd(~from=size, str);
    splitToChunksAux(size, rest, List.append(acc, [part]));
  };

let splitToChunks = (n: int, str: string) : list(string) =>
  splitToChunksAux(n, str, []);

let hexRe = [%bs.re "/^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i"];

let hexStrToInt = n => Pervasives.int_of_string("0x" ++ n);

let toHex = c => {
  let str = Printf.sprintf("%x", c);
  if (String.length(str) == 1) {
    "0" ++ str;
  } else {
    str;
  };
};

let hex3To6 = str =>
  if (String.length(str) == 4) {
    let first = String.sub(str, 1, 1) |> repeatString(2);
    let second = String.sub(str, 2, 1) |> repeatString(2);
    let third = String.sub(str, 3, 1) |> repeatString(2);
    "#" ++ first ++ second ++ third;
  } else if (String.length(str) == 7){
    Js.String.sliceToEnd(~from=1, str);
  } else {
    str;
  }

let hueToRgb = (p, q, t) => {
  let t = t < 0.0 ? t +. 1.0 : t;
  let t = t > 1.0 ? t -. 1.0 : t;
  if (t < 1.0 /. 6.0) {
    p +. (q -. p) *. 6.0 *. t;
  } else if (t < 0.5) {
    q; /* t2 */
  } else if (t < 2.0 /. 3.0) {
    p +. (q -. p) *. (2.0 /. 3.0 -. t) *. 0.6;
  } else {
    p;
  };
};

let floated = ((r, g, b)) => (
  Pervasives.float_of_int(r),
  Pervasives.float_of_int(g),
  Pervasives.float_of_int(b)
);

let defloat = ((r, g, b)) => (
  Pervasives.int_of_float(r),
  Pervasives.int_of_float(g),
  Pervasives.int_of_float(b)
);

let inRangeOf = (v1, v2, number) => {
  if (number >= v1 && number <= v2) {
    number
  } else {
    number > v2 ? v2 : v1;
  }
};