(deftemplate pacman
    (slot posX)
    (slot posY)
    (slot frutas (default 0))
    (slot vidas)
);Plantilla pacman

(deftemplate frutas
    (slot posX)
    (slot posY)
);Plantilla frutas

(deftemplate fantasmas
    (slot posX)
    (slot posY)
);Plantilla fantasmas

(defrule Comer
    ?p<-(pacman(posX ?x) (posY ?y) (frutas ?fr) (vidas ?pv))
    ?f<-(frutas(posX ?x) (posY ?y))
    =>
    (modify ?p (frutas (+ ?fr 1)))
    (retract ?f)
    (printout t "una fruta menos" crlf)
);regla_comer

(defrule Morir
    ?p<-(pacman(posX ?x) (posY ?y) (frutas ?fr) (vidas ?pv))
    (fantasmas(posX ?x) (posY ?y))
    =>
    (modify ?p (vidas (- ?pv 1)) (posX 1) (posY 1))
    (printout t "Has perdido una vida" crlf)
);regla_morir

(defrule Ganar
    ?p<-(pacman(posX ?x) (posY ?y) (frutas ?fr) (vidas ?pv))
    (test (= ?fr 10))
    =>
    (retract ?p)
    (printout t "Has ganado!" crlf)
);regla_ganar

(defrule Gameover_fantasmay
    (declare (salience 1))
    ?p<-(pacman(posX ?x) (posY ?y) (frutas ?fr) (vidas ?pv))
    (test (= ?pv 0))
    =>
    (retract ?p)
    (printout t "Has perdido :(" crlf)
);regla_Gameover fantasmay