// SequenceGenerator.io
// the first way...

SequenceGenerator := Object clone do(
  odd := method(n,
    outList := list();
    for(i, 1, n, outList append(2 * i - 1));
    outList
  );
  even := method(n,
    outList := list();
    for(i, 0, n-1, outList append(2 * i));
    outList
  );
  natural := method(n,
    outList := list();
    for(i, 1, n, outList append(i));
    outList
  )
)