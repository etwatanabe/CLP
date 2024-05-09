perm5(A,B,C,D,E) :-
    neq5(A,B,C,D,E).

neq5(A,B,C,D,E) :-
    neq(A,B), neq(A,C), neq(A,D), neq(A,E),
	neq(B,C), neq(B,D), neq(B,E),
	neq(C,D), neq(C,E),
	neq(D,E).

neq(1, 2). neq(1, 3). neq(1, 4). neq(1, 5).
neq(2, 1). neq(2, 3). neq(2, 4). neq(2, 5).
neq(3, 1). neq(3, 2). neq(3, 4). neq(3, 5).
neq(4, 1). neq(4, 2). neq(4, 3). neq(4, 5).
neq(5, 1). neq(5, 2). neq(5, 3). neq(5, 4).