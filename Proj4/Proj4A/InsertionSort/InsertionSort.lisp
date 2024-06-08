(defun insertion-sort (array)
  (loop for i from 1 below (length array) do
    (let ((key (elt array i))
          (j (- i 1)))
      (loop while (and (>= j 0) (> (elt array j) key)) do
        (setf (elt array (+ j 1)) (elt array j))
        (decf j))
      (setf (elt array (+ j 1)) key)))
  array)

(defun main ()
  (let ((array #(12 11 13 5 6)))
    (insertion-sort array)
    (format t "~{~a~^ ~}~%" array)))

(main)
