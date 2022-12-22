(deffacts BaseHechos
    (ubicacion A norte D)
    (ubicacion A oeste B)
    (ubicacion B norte E)
    (ubicacion B oeste C)
    (ubicacion C norte F)
    (ubicacion D norte G)
    (ubicacion D oeste E)
    (ubicacion E norte H)
    (ubicacion E oeste F)
    (ubicacion F norte I)
    (ubicacion G oeste H)
    (ubicacion H oeste I)
); Base de hechos

(defrule sur
    (ubicacion ?c1 norte ?c2)
    =>
    (assert (ubicacion ?c2 sur ?c1))
    ;(printout t "Ubicacion "?c2" esta al sur de la ubicacion "?c1"."crlf)
)

(defrule este
    (ubicacion ?c1 oeste ?c2)
    =>
    (assert (ubicacion ?c2 este ?c1))
    ;(printout t "ubicacion "?c2" esta al este de la ubicacion "?c1"."crlf)
)

(defrule t_norte
    (ubicacion ?c1 norte ?c2)
    (ubicacion ?c2 norte ?c3)
    =>
    (assert (ubicacion ?c1 norte ?c3))
    ;(printout t "ubicacion "?c1" esta al norte de la ubicacion "?c3"."crlf)
)

(defrule t_sur
    (ubicacion ?c1 sur ?c2)
    (ubicacion ?c2 sur ?c3)
    =>
    (assert (ubicacion ?c1 sur ?c3))
    ;(printout t "ubicacion "?c1" esta al sur de la ubicacion "?c3"."crlf)
)

(defrule t_este
    (ubicacion ?c1 este ?c2)
    (ubicacion ?c2 este ?c3)
    =>
    (assert (ubicacion ?c1 este ?c3))
    ;(printout t "ubicacion "?c1" esta al este de la ubicacion "?c3"."crlf)
)

(defrule t_oeste
    (ubicacion ?c1 oeste ?c2)
    (ubicacion ?c2 oeste ?c3)
    =>
    (assert (ubicacion ?c1 oeste ?c3))
    ;(printout t "ubicacion "?c1" esta al oeste de la ubicacion "?c3"."crlf)    
)

(defrule noroeste
    (ubicacion ?c1 oeste ?c3)
    (ubicacion ?c2 sur ?c3)
    =>
    (assert (ubicacion ?c1 noroeste ?c2))
    ;(printout t "ubicacion "?c1" esta al noroeste de la ubicacion "?c2"."crlf)   
)

(defrule noreste
    (ubicacion ?c1 este ?c3)
    (ubicacion ?c2 sur ?c3)
    =>
    (assert (ubicacion ?c1 noreste ?c2))
    ;(printout t "ubicacion "?c1" esta al noreste de la ubicacion "?c2"."crlf)
)

(defrule suroeste
    (ubicacion ?c1 oeste ?c3)
    (ubicacion ?c2 norte ?c3)
    =>
    (assert (ubicacion ?c1 suroeste ?c2))
    ;(printout t "ubicacion "?c1" esta al suroeste de la ubicacion "?c2"."crlf)
)

(defrule sureste
    (ubicacion ?c1 este ?c3)
    (ubicacion ?c2 norte ?c3)
    =>
    (assert (ubicacion ?c1 sureste ?c2))
    ;(printout t "ubicacion "?c1" esta al sureste de la ubicacion "?c2"."crlf)
)

(defrule inicio
    ?f1 <- (situacion ?x ?y)
    (ubicacion ?x ?u ?y)
    =>
    (printout t ?x" esta al "?u" de "?y crlf)
    (retract ?f1)
)