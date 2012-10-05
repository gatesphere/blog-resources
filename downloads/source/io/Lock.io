// Lock
// a basic lock (non-reentrant style)
// Jacob Peck
// 20111024

Lock := Object clone do(
  // state
  locked ::= false;
  possessor ::= nil;
  
  // constructor
  init := method(
    self setLocked(false);
    self setPossessor(nil);
  );
  
  // methods
  lock := method(
    while(self locked, nil); // block while locked
    self setLocked(true);
    self setPossessor(call sender);
    self
  );
  
  unlock := method(
    currentsender = call sender;
    if(self locked and self possessor == currentsender, // unlock if locked and called from the right object
      self setPossessor(nil);
      self setLocked(false);
    );
    self
  )
)