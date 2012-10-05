;; elo calc
;; Jacob Peck (http://suspended-chord.info/)
;; 20110630
;; Public domain

(setf *k* 24)

(setf *a* 0)
(setf *b* 0)

(defmethod calculate-elo ((rating-a float) (rating-b float) (score float) &aux ea eb)
  (setf ea (/ 1 (+ 1 (expt 10 (/ (- rating-b rating-a) 400)))))
  (setf eb (/ 1 (+ 1 (expt 10 (/ (- rating-a rating-b) 400)))))
  (setf *a* (+ rating-a (* *k* (- score ea))))
  (setf *b* (+ rating-b (* *k* (- (- 1 score) eb))))
  NIL
)

(defmethod run (&aux work score olda oldb)
  (format t "Rating of player A: ")
  (setf *a* (read))
  (format t "Rating of player B: ")
  (setf *b* (read))
  (setf work t)
  (loop while work do
    (setf olda *a*)
    (setf oldb *b*)
    (format t "Score (1 = A wins, .5 = draw, 0 = B wins): ")
    (setf score (read))
    (calculate-elo (float *a*) (float *b*) (float score))
    (format t "Player A's new rating: ~A (~A)~%" *a* (- *a* olda))
    (format t "Player B's new rating: ~A (~A)~%" *b* (- *b* oldb))
    (format t "Go again? ")
    (setf work (read))
  )
  NIL
)

(run)