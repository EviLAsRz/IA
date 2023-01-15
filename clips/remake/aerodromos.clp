(deftemplate aeronave
    (slot id)
    (slot company)
    (slot origen)
    (slot destino)
    (slot velActual)
    (slot peticion (allowed-values Ninguna Despegue Aterrizaje Emergencia Rumbo))
    (slot estado (default enTierra) (allowed-values enTierra Ascenso Crucero Descenso))
)

(deftemplate aerodromo
    (slot id)
    (slot ciudad)
    (slot estado (allowed-values ON OFF))
    (slot radioVisibilidad)
    (slot velViento)
)

(deftemplate piloto
    (slot id)
    (slot accion (default Stand-by) (allowed-values OK SOS Ejecutando Stand-by))
)

(deftemplate vuelo
    (slot idAerodromo1)
    (slot idAerodromo2)
    (slot distancia)
    (slot velDespegue (default 240))
    (slot velCrucero (default 700))
)

(deffunction tiempoHoras (?vel ?dist)
    (if (> ?dist ?vel) then
        (bind ?dist (div ?dist ?vel))
        return ?dist
    )else return 0
)

(deffunction tiempoMinutos (?vel ?dist)
    (bind ?dist (mod ?dist ?vel))
    (bind ?dist (/ ?dist ?vel))
    (bind ?dist (round(* ?dist 60)))
    return ?dist
)


(defrule Despegar
    ?nave<-(aeronave (id ?idAero) (company ?cAero) (origen ?oAero) (destino ?dAero) (velActual ?vaAero) (peticion Despegue) (estado enTierra))
    ?piloto<-(piloto (id ?idAero) (accion OK))
    ?aeroOrigen<-(aerodromo (id ?idDromo1) (ciudad ?oAero) (estado ON) (radioVisibilidad ?rDromo1) (velViento ?vDromo1))
    ?aeroDestino<-(aerodromo (id ?idDromo2) (ciudad ?dAero))
    ?vuelo<-(vuelo (idAerodromo1 ?idDromo1) (idAerodromo2 ?idDromo2) (distancia ?vDis) (velDespegue ?vDes) (velCrucero ?vCru))
    (test (neq ?idDromo1 ?idDromo2))
    (test (> ?rDromo1 5))
    (test (< ?vDromo1 75))
    =>
    (modify ?piloto (accion Ejecutando))
    (modify ?nave  (velActual ?vDes) (peticion Ninguna) (estado Ascenso))
    (printout t "La aeronave "?idAero" de la compania "?cAero" va a realizar la accion "Despegue" desde el aerodromo "?idDromo1" de "?oAero" con destino "?dAero"." crlf)
)

(defrule excepcion
    ?nave<-(aeronave (id ?idAero) (company ?cAero) (origen ?oAero) (destino ?dAero) (peticion Despegue))
    ?piloto<-(piloto (id ?idAero) (accion ?aPiloto))
    ?aeroOrigen<-(aerodromo (id ?idDromo1) (ciudad ?oAero) (estado ON) (radioVisibilidad ?rDromo1) (velViento ?vDromo1))
    ?vuelo<-(vuelo (idAerodromo1 ?idDromo1) (idAerodromo2 ?idDromo2) (distancia ?vDis) (velDespegue ?vDes) (velCrucero ?vCru))
    (test (neq ?aPiloto OK))
    =>
    (modify ?nave (peticion Emergencia))
    (printout t "El piloto de la aeronave "?idAero" de la compania "?cAero" no se encentra disponible para iniciar el despegue desde el aerodromo "?idDromo1" de "?oAero" con destino "?dAero"." crlf)
)

(defrule crucero
    ?nave<-(aeronave (id ?idAero) (origen ?oAero) (destino ?dAero) (velActual ?vaAero) (peticion Despegue) (estado Ascenso))
    ?piloto<-(piloto (id ?idAero) (accion Ejecutando))
    ?aeroOrigen<-(aerodromo (id ?idDromo1) (ciudad ?oAero) (estado ON) (radioVisibilidad ?rDromo1) (velViento ?vDromo1))
    ?aeroDestino<-(aerodromo (id ?idDromo2) (ciudad ?dAero))
    ?vuelo<-(vuelo (idAerodromo1 ?idDromo1) (idAerodromo2 ?idDromo2) (distancia ?vDis) (velDespegue ?vDes) (velCrucero ?vCru))
    =>
    (modify ?nave (estado Crucero) (velActual ?vCru))
    (modify ?piloto (accion Stand-by))
    (bind ?horas (tiempoHoras ?vCru ?vDis))
    (bind ?minutos (tiempoMinutos ?vCru ?vDis))

    (printout t "La nave "?idAero" con destino "?dAero" tardará aproximadamente "?horas" horas y "?minutos" minutos." crlf)
)
