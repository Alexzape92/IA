(deftemplate Personal
	(slot DNI)
	(slot Nombre)
	(slot Turno (allowed-values mannana tarde ambos))
	(slot Ventas)
	(slot Encargado (allowed-values Si No))
)

(deftemplate Proucto
	(slot Id)
	(slot Nombre)
	(slot Cafete (type INTEGER))
	(slot Almacen (type INTEGER))
	(slot Precio (type FLOAT))
	(slot Maximo (default 30))
)

(deftemplate Ventas
	(slot Pers)
	(slot Prod)
	(slot Ud)
	(slot Pago (allowed-values tarjeta bono efectivo))
)

(defrule AsignarVenta
	?prod <- (Producto (Id ?id) (Cafete ?stock) (Precio ?precio))
	?pers <- (Personal (DNI ?dni) (Ventas ?ventas))
	?venta <- (Ventas (Pers ?dni) (Prod ?id) (Ud ?ud))
	(test (>= ?stock ?ud))
	=>
	(bind ?nuevo_total (+ ?ventas (* ?precio ?ud)))	;LA VARIABLE VENTAS ES "POR COPIA", AUNQUE YO MAS TARDE CAMBIE EL SLOT VENTAS, ?ventas NO 						 CAMBIA
	(modify ?prod (Cafete (- ?stock ?ud)))
	(modify ?pers (Ventas (+ ?ventas (* ?precio ?ud))))
	(println ?nuevo_total)
	(retract ?venta)
)

(deffunction REPOSICION (?act ?alm ?max)
	(bind ?aux (- ?max ?act))
	(if (>= ?alm ?aux) then
		(return ?aux)
	else
		(return ?alm)
	)
)

(defrule Reponer
	?prod <- (Producto (Cafete ?stock) (Almacen ?alm) (Maximo ?max))
	(test (< ?stock 10))
	(test (> ?alm 0)) 	;Para evitar bucles si stock + alm < 10
	=>
	(bind ?aux (REPOSICION ?act ?alm ?max))
	(modify ?prod (Cafete (+ ?aux ?stock)) (Almacen(- ?alm ?aux)))
	
	
	
	
	
	
	
	
	
