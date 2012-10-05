// SequenceGenerator2.io
// approaching the "next" way

SequenceGenerator2 := Object clone do(
  // use these
  odd := method(n,
    genSeq(n,1,2)
  );
  even := method(n,
    genSeq(n,0,2)
  );
  natural := method(n,
    genSeq(n,1,1)
  );
  
  // helpers - actually do all the work
  next := method(current, step,
    current + step
  );
  genSeq := method(n, start, step,
    outList := list();
    curVal := start;
    for(i, 1, n,
      outList append(curVal);
      curVal := next(curVal, step)
    );
    outList
  )
)
