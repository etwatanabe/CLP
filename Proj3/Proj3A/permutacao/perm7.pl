perm7(A,B,C,D,E,F,G) :-
    neq7(A,B,C,D,E,F,G).

neq7(A,B,C,D,E,F,G) :-
    neq(A,B), neq(A,C), neq(A,D), neq(A,E), neq(A,F), neq(A,G),
	neq(B,C), neq(B,D), neq(B,E), neq(B,F), neq(B,G),
	neq(C,D), neq(C,E), neq(C,F), neq(C,G),
	neq(D,E), neq(D,F), neq(D,G),
	neq(E,F), neq(E,G),
	neq(F,G).

neq(1, 2). neq(1, 3). neq(1, 4). neq(1, 5). neq(1, 6). neq(1, 7).
neq(2, 1). neq(2, 3). neq(2, 4). neq(2, 5). neq(2, 6). neq(2, 7).
neq(3, 1). neq(3, 2). neq(3, 4). neq(3, 5). neq(3, 6). neq(3, 7).
neq(4, 1). neq(4, 2). neq(4, 3). neq(4, 5). neq(4, 6). neq(4, 7).
neq(5, 1). neq(5, 2). neq(5, 3). neq(5, 4). neq(5, 6). neq(5, 7).
neq(6, 1). neq(6, 2). neq(6, 3). neq(6, 4). neq(6, 5). neq(6, 7).
neq(7, 1). neq(7, 2). neq(7, 3). neq(7, 4). neq(7, 5). neq(7, 6).