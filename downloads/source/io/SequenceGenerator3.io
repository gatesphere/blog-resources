// SequenceGenerator3.io
// the "next" way

// to make a generic sequence,
// call:
//  SequenceGenerator3 genSeq(numValues, startValue, nextFunction)
// where numValues is how many values you want in the sequence
// startValue is the initial value,
// and nextFunction takes the form of:
// block(x, newX), where newX is any legal expression.

// example:
// Io> SequenceGenerator3 genSeq(8,1,block(x,x*2))
// ==> list(1, 2, 4, 8, 16, 32, 64, 128)


SequenceGenerator3 := Object clone do(
  odd := method(n,
    genSeq(n,1,block(x,x+2))
  );
  even := method(n,
    genSeq(n,0,block(x,x+2))
  );
  natural := method(n,
    genSeq(n,1,block(x,x+1))
  );
  genSeq := method(n, start, next,
    outList := list();
    curVal := start;
    for(i, 1, n,
      outList append(curVal);
      curVal :=  next call(curVal)
    );
    outList
  )
)