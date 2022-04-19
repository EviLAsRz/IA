(deftemplate Via
    (slot idvia)
    (slot nombrevia)
    (slot numvehiculos (default 0))
)

(deftemplate Semaforo
    (slot idsemaforo)
    (slot idvia)
    (slot estado (allowed-values Rojo Verde))
    (slot numvehiculos (default 0))
)

(deftemplate Sensor
    (slot idcelula (allowed-values 1 2 3))
    (slot idsemaforo)
    (slot estado (allowed-values activada desactivada)(default desactivada))
    (slot matricula)    
)

(deftemplate Vehiculo
    (slot matricula)
    (slot tipo (allowed-values automovil camion motocicleta bicicleta))
    (slot idsemaforo)
    (slot accion (allowed-values llegando esperando cruzando realizado nada)(default nada))
)

(deffacts BasedeDatas
    (Sensor(idcelula 1)(idsemaforo A)(estado desactivada)(matricula 2345FFT))
    (Sensor(idcelula 2)(idsemaforo B)(estado activada)(matricula 2345FFT))
    (Semaforo(idsemaforo A)(idvia A)(estado Verde))
    (Semaforo(idsemaforo B)(idvia B)(estado Verde))
    (Via(idvia A)(nombrevia Constitución))
    (Via (idvia B)(nombrevia Falla))
    (activar_sensor 1 A 2345FFT camión)
)

(defrule llegando_V
    ?as<-(activar_sensor 1 ?idf ?m ?t)
    ?s1<-(Sensor (idcelula 1)(idsemaforo ?idf)(estado desactivada)(matricula ?m))
    (Semaforo (idsemaforo ?idf)(idvia ?idv)(estado Verde))
    (Via (idvia ?idv)(nombrevia ?nv))
    =>
    (assert (Vehiculo(matricula ?m)(tipo ?t)(idsemaforo ?idf)(accion cruzando)))
    (modify ?s1(estado activada))
    (printout t "El sensor S" ?idf 1 " acaba de ser activado por el/la "?t " con matrícula " ?m " en la vía " ?nv "." crlf)
    (retract ?as)
)

(defrule llegando_R
    ?as<-(activar_sensor 1 ?idf ?m ?t)
    ?s1<-(Sensor (idcelula 1)(idsemaforo ?idf)(estado desactivada)(matricula ?m))
    (Semaforo (idsemaforo ?idf)(idvia ?idv)(estado Rojo))
    (Via (idvia ?idv)(nombrevia ?nv))
    =>
    (assert (Vehiculo(matricula ?m)(tipo ?t)(idsemaforo ?idf)(accion esperando)))
    (modify ?s1(estado activada))
    (printout t "El sensor S" ?idf 1 " acaba de ser activado por el/la "?t " con matrícula " ?m " en la vía " ?nv "." crlf)
    (retract ?as)
)

(defrule cruzando
    (declare (salience 10))
    ?sf1<-(Semaforo (idsemaforo ?idf1)(idvia ?id1)(estado Verde)(numvehiculos ?nvh1))
    ?sf2<-(Semaforo (idsemaforo ?idf2)(idvia ?id2)(estado Verde)(numvehiculos ?nvh2))
    ?v1<-(Vehiculo (matricula ?m)(tipo ?t)(idsemaforo ?idf1)(accion esperando|llegando))
    (Via (idvia ?idv1)(nombrevia ?nv1))
    (Via (idvia ?idv2)(nombrevia ?nv2))
    ?s1<-(Sensor (idcelula 1)(idsemaforo ?idsf1)(estado activada)(matricula ?m))
    ?s2<-(Sensor (idcelula 2)(idsemaforo ?idsf2)(estado activada)(matricula ?m))
    (test (neq ?idf1 ?idf2))
    (test (neq ?idsf1 ?idsf2))
    (test (neq ?id1 ?id2))
    (test (neq ?idv1 ?idv2))
    (test (neq ?nv1 ?nv2))
    =>
    (modify ?s1 (estado desactivada))
    (modify ?s2 (estado desactivada))
    (modify ?v1 (accion cruzando))
    (modify ?sf1 (numvehiculos (+ ?nvh1 1)))
    (modify ?sf1 (numvehiculos (+ ?nvh2 1)))
    (printout t "El/la "?t" con matrícula "?m" está cruzando la vía "?nv1" con la vía "?nv2 crlf)
)