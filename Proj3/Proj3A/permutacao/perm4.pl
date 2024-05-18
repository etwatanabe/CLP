perm4(A,B,C,D) :-
    neq4(A,B,C,D).

neq4(A,B,C,D) :-
    neq(A,B), neq(A,C), neq(A,D),
	neq(B,C), neq(B,D),
	neq(C,D).

neq(1, 2). neq(1, 3). neq(1, 4).
neq(2, 1). neq(2, 3). neq(2, 4).
neq(3, 1). neq(3, 2). neq(3, 4).
neq(4, 1). neq(4, 2). neq(4, 3).