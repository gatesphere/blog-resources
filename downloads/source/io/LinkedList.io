// LinkedList.io
// a singly-linked list in Io
// 20111017

LinkedList := Object clone do(
  // state
  head ::= nil;
  
  // constructor
  init := method(
    head = nil
  );
  
  // methods
  isEmpty := method(
    self head == nil
  );
  size := method(
    pointer := self head;
    sz := 0;
    while(pointer != nil,
      sz = sz + 1;
      pointer = pointer next
    );
    sz
  );
  add := method(n,
    if(self head == nil,
      self setHead(LinkedListNode clone)
    );
    self head add(n);
    nil
  );
  find := method(n,
    if(self head == nil, return false);
    self head find(n)
  );
  remove := method(n,
    if(self head == nil, return nil);
    if(self head value == n,
      self setHead(self head next),
      self head remove(n)
    );
    nil
  )
)

LinkedListNode := Object clone do(
  // state
  value ::= nil;
  next ::= nil;
  
  // constructor
  init := method(
    value = nil;
    next = nil
  );
  
  // methods
  add := method(n,
    if(self value == nil,
      self setValue(n),
      if (self next == nil,
        self setNext(LinkedListNode clone)
      );
      self next add(n)
    );
    nil
  );
  find := method(n,
    if(self value == nil, return false);
    if(self value == n, return true,
      if(self next == nil, return false, self next find(n))
    )
  );
  remove := method(n,
    if(self next == nil, return nil);
    if(self next value == n,
      self setNext(self next next),
      self next remove(n)
    );
    nil
  )
)