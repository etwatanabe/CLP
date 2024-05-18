perm6(A,B,C,D,E,F) :-
    neq6(A,B,C,D,E,F).

neq6(A,B,C,D,E,F) :-
    neq(A,B), neq(A,C), neq(A,D), neq(A,E), neq(A,F),
	neq(B,C), neq(B,D), neq(B,E), neq(B,F),
	neq(C,D), neq(C,E), neq(C,F),
	neq(D,E), neq(D,F),
	neq(E,F).

neq(1, 2). neq(1, 3). neq(1, 4). neq(1, 5). neq(1, 6).
neq(2, 1). neq(2, 3). neq(2, 4). neq(2, 5). neq(2, 6).
neq(3, 1). neq(3, 2). neq(3, 4). neq(3, 5). neq(3, 6).
neq(4, 1). neq(4, 2). neq(4, 3). neq(4, 5). neq(4, 6).
neq(5, 1). neq(5, 2). neq(5, 3). neq(5, 4). neq(5, 6).
neq(6, 1). neq(6, 2). neq(6, 3). neq(6, 4). neq(6, 5).