(deftemplate coche
    (slot modelo (allowed-values modelo1 modelo2 modelo3 modelo4 modelo5))
    (slot precio)
    (slot maletero (allowed-values pequeno mediano grande))
    (slot caballos)
    (slot abs (allowed-values si no))
    (slot consumo)
)

(deftemplate cliente
    (slot precio (default 13000))
    (slot maletero (allowed-values pequeno mediano grande)(default grande))
    (slot caballos (default 80))
    (slot abs (allowed-values si no)(default si))
    (slot consumo (default 8))
)

(deffacts BaseHechos
    (coche (modelo modelo1) (precio 12000) (maletero pequeno) (caballos 65) (abs no) (consumo 4.7))
    (coche (modelo modelo2) (precio 12500) (maletero pequeno) (caballos 80) (abs si) (consumo 4.9))
    (coche (modelo modelo3) (precio 13000) (maletero mediano) (caballos 100) (abs si) (consumo 7.8))
    (coche (modelo modelo4) (precio 14000) (maletero grande) (caballos 125) (abs si) (consumo 6))
    (coche (modelo modelo5) (precio 15000) (maletero pequeno) (caballos 147) (abs si) (consumo 8.5))
)

(defrule recomendacion
    ?cl<-(cliente (precio ?pre) (maletero ?m) (caballos ?cab) (abs ?a) (consumo ?con))
    ?co<-(coche (modelo ?mod) (precio ?prec) (maletero ?mc) (caballos ?cabc) (abs ?ac) (consumo ?conc))
    (test (>= ?pre ?prec))
    (test (eq ?m ?mc))
    (test (>= ?cab ?cabc))
    (test (eq ?a ?ac))
    (test (>= ?con ?conc))
    =>
    (printout t "Al cliente se le recomienda el "?mod"." crlf)
)