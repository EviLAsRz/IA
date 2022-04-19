(deftemplate coche
    (slot modelo (allowed-values modelo1 modelo2 modelo3 modelo4 modelo5))
    (slot precio)
    (slot maletero (allowed-values pequeno mediano grande))
    (slot caballos)
    (slot ABS (allowed-values no si))
    (slot consumo)
);Coche

(deffacts baseFacts
    (coche (modelo modelo1) (precio 12000) (maletero pequeno) (caballos 65) (ABS no) (consumo 4.7))
    (coche (modelo modelo2) (precio 12500) (maletero pequeno) (caballos 80) (ABS si) (consumo 4.9))
    (coche (modelo modelo3) (precio 13000) (maletero mediano) (caballos 100) (ABS si) (consumo 7.8))
    (coche (modelo modelo4) (precio 14000) (maletero grande) (caballos 125) (ABS si) (consumo 6.0))
    (coche (modelo modelo5) (precio 15000) (maletero pequeno) (caballos 147) (ABS si) (consumo 8.5))
);Base de hechos de los coches del concesionario

(deftemplate usuario
    (slot precio (default 13000))
    (slot maletero (allowed-values pequeno mediano grande) (default grande))
    (slot caballos (default 80))
    (slot ABS (allowed-values no si) (default si))
    (slot consumo (default 8))
);Usuario

(defrule formulario
    =>
    (printout t "Presupuesto: ")
    (bind ?presupuesto (read))
    (printout t "Tipo de maletero: ")
    (bind ?maletero (read))
    (printout t "ABS: ")
    (bind ?abs (read))
    (printout t "Caballos: ")
    (bind ?caballos (read))
    (printout t "consumo medio: ")
    (bind ?consumo (read))
    =>
    (assert (usuario (precio ?presupuesto) (maletero ?maletero)
    (caballos ?caballos) (ABS ?abs) (consumo ?consumo)))
);formulario

(defrule Recomendacion
    ?u<-(usuario (precio ?presupuesto) (maletero ?maletero)
        (caballos ?caballos) (ABS ?abs) (consumo ?consumo))
    ?cf<-(coche (modelo ?mo) (precio ?p) (maletero ?m)
        (caballos ?c) (ABS ?ab) (consumo ?con))
    (test (>= ?presupuesto ?p))
    (test (eq ?maletero ?m))
    (test (<= ?caballos ?c))
    (test (eq ?abs ?ab))
    (test (>= ?consumo ?con))
    =>
    (printout t "Se le recomienda al usuario el " ?mo crlf)
);recomendacion
