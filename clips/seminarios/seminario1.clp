(deffacts BaseFacts
    (tienePelo Robi)
    (colorLeonardo Robi)
    (rayasNegras Robi)
    (tienePluma Susi)
    (colorBlanco Susi)
    (vuela Susi)
    (comeCarne Robi)
    (comePescado Susi)
);Data

(defrule R1
    (tienePelo ?name)
    => 
    (assert (mamifero ?name))
    (printout t ?name " es un mamifero" crlf)
);mamifero

(defrule R2
    (daLeche ?name)
    => 
    (assert (mamifero ?name))
    (printout t ?name " es un mamifero" crlf)
);mamifero

(defrule R3
    (tienePluma ?name)
    =>
    (assert (ave ?name))
    (printout t ?name " es un ave" crlf)
);ave

(defrule R4
    (vuela ?name)
    (tienePluma ?name)
    => 
    (assert (ave ?name))
    (printout t ?name " es un ave" crlf)
);ave

(defrule R5
    (comeCarne ?name)
    => 
    (assert (carnivoro ?name))
    (printout t ?name " es carnivoro" crlf)
);carnivoro

(defrule R6
    (tieneDientesPuntiagudos ?name)
    (tieneGarras ?name)
    (tieneOjosFrente ?name)
    => 
    (assert (carnivoro ?name))
    (printout t ?name " es carnivoro" crlf)
);carnivoro

(defrule R7
    (mamifero ?name)
    (tienePezuñas ?name)
    => 
    (assert (ungulado ?name))
    (printout t ?name " es ungulado" crlf)
);ungulado

(defrule R8
    (mamifero ?name)
    (rumia ?name)
    => 
    (assert (ungulado ?name))
    (printout t ?name " es ungulado" crlf)
);ungulado

(defrule R9
    (mamifero ?name)
    (carnivoro ?name)
    (colorLeonardo ?name)
    (manchasOscuras ?name)
    => 
    (assert (leopardo ?name))
    (printout t ?name " es un leopardo" crlf)
);Leopardo

(defrule R10
    (mamifero ?name)
    (carnivoro ?name)
    (colorLeonardo ?name)
    (rayasNegras ?name)
    => 
    (assert (tigre ?name))
    (printout t ?name " es un tigre" crlf)
);tigre

(defrule R11
    (ungulado ?name)
    (cuelloLargo ?name)
    (piernasLargas ?name)
    (manchasOscuras ?name)
    => 
    (assert (jirafa ?name))
    (printout t ?name " es una jirafa" crlf)
);jirafa

(defrule R12
    (ungulado ?name)
    (rayasNegras ?name)
    => 
    (assert (cebra ?name))
    (printout t ?name " es una cebra" crlf)
);cebra

(defrule R15
    (ave ?name)
    (vuela ?name)
    (comePescado ?name)
    => 
    (assert (Albatros ?name))
    (printout t ?name " es un Albatros" crlf)
)