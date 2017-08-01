<?php
	class BaseDatos
	{
		static function abrirConexion()
		{	
			$conn = new mysqli("localhost", "root", "", "librovisitas");	
			$conn->set_charset("utf8");
			
			return $conn;
		}
		
		static function cerrarConexion ($conn)
		{
			$conn->close();	
		}
		/////////////////////////////////////////
		// FUNCIONES RELACIONADAS CON USUARIOS //
		/////////////////////////////////////////
		
		// Agrega un nuevo usuario
		static function agregarUsuario ($persona)
		{
			var_dump($persona);	
			$conn = self::abrirConexion();
			
			$sql = "INSERT INTO usuarios (email, pwd, user, nombre, color, intentos)
			VALUES ('" . $persona->get_email() . "', '" . $persona->get_password() . "', '" . $persona->get_alias() . "', '" . $persona->get_nombre() . "', '" . $persona->get_color() . "', " . $persona->get_errores() . ")";
			$conn->query($sql);
			
			self::cerrarConexion($conn);
		}
		
		// Elimina un usuario
		static function eliminarUsuario ($clave)
		{			
			$conn = self::abrirConexion();		
			$borrar = "DELETE FROM usuarios WHERE email='" . $clave . "'";		
			$conn->query($borrar);			
			self::cerrarConexion($conn);
		}
		
		// Obtenemos un usuario determinado
		static function getUsuario ($clave)
		{				
			$conn = self::abrirConexion();			
			$select = "SELECT * FROM usuarios WHERE email='" . $clave . "'";
			$result = $conn->query($select);			
			$resultado = $result->fetch_all(MYSQLI_ASSOC);	
			self::cerrarConexion($conn);						
						
			return (count($resultado) == 0) ? NULL : new Usuario($resultado[0]['email'], $resultado[0]['pwd'], $resultado[0]['user'], $resultado[0]['nombre'], $resultado[0]['color'], $resultado[0]['intentos']);;
		}
		
		// Obtenemos un usuario determinado
		static function getUsuarioPorAlias ($alias)
		{				
			$conn = self::abrirConexion();			
			$select = "SELECT * FROM usuarios WHERE user='" . $alias . "'";
			$result = $conn->query($select);			
			$resultado = $result->fetch_all(MYSQLI_ASSOC);	
			self::cerrarConexion($conn);						
						
			return (count($resultado) == 0) ? NULL : new Usuario($resultado[0]['email'], $resultado[0]['pwd'], $resultado[0]['user'], $resultado[0]['nombre'], $resultado[0]['color'], $resultado[0]['intentos']);;
		}
		
		// Obtiene todos los usuarios
		static function getUsuarios ()
		{				
			$conn = self::abrirConexion();			
			$select = "SELECT * FROM usuarios";
			$result = $conn->query($select);
			$resultado = array();								
			while ($obj  = mysqli_fetch_object($result))
			{
				$user = new Usuario($obj->email, $obj->pwd, $obj->user, $obj->nombre, $obj->color, $obj->intentos);		
				array_push($resultado, $user);
			}						
			self::cerrarConexion($conn);								
			return $resultado;
		}
		
		// Actualiza los datos de un usuario concreto
		static function actualizarUsuario ($clave, $persona)
		{			
			$conn = self::abrirConexion();			
			$update = "UPDATE usuarios SET email='" . $persona->get_email() . "', pwd='" . $persona->get_password() . "', user='" . $persona->get_alias() . "', nombre='" . $persona->get_nombre(). "', color='" . $persona->get_color() . "', intentos='" . $persona->get_errores() . "'  WHERE email='" . $clave . "'";
			$conn->query($update);			
			self::cerrarConexion($conn);
		}
		
		/*static function setErrores ($clave, $errores)
		{			
			$conn = self::abrirConexion();			
			$update = "UPDATE usuarios SET intentos='" . $errores . "'  WHERE email='" . $clave . "'";
			$conn->query($update);			
			self::cerrarConexion($conn);
		}*/
		
		/////////////////////////////////////////
		// FUNCIONES RELACIONADAS CON MENSAJES //
		/////////////////////////////////////////
		
		// Agrega un mensaje nuevo
		static function agregarMensaje ($persona, $mensaje)
		{			
			$conn = self::abrirConexion();			
			$sql = "INSERT INTO comentarios (idUser, titulo, mensaje)
			VALUES ('" . $persona->get_email() . "', '" . $mensaje->get_titulo() . "', '" . $mensaje->get_mensaje() . "')";
			$conn->query($sql);			
			self::cerrarConexion($conn);
		}
		
		// Elimina un mensaje
		static function eliminarMensaje ($id)
		{			
			$conn = self::abrirConexion();		
			$borrar = "DELETE FROM comentarios WHERE id='" . $id . "'";		
			$conn->query($borrar);			
			self::cerrarConexion($conn);
		}
		
		// Obtiene todos los mensajes de un determinado usuario
		static function getMensajesDe ($idUser, $pagina)
		{				
			$conn = self::abrirConexion();			
			$select = "SELECT * FROM comentarios WHERE idUser='" . $idUser . "' ORDER BY fecha DESC LIMIT 3 OFFSET " . (3 * ($pagina - 1)) ;
						
			$result = $conn->query($select);
			$resultado = array();
						
			while ($obj  = mysqli_fetch_object($result))
			{
				$mensaje = new Mensaje($obj->id, $obj->idUser, $obj->titulo, $obj->mensaje, $obj->fecha);				
				array_push($resultado, $mensaje);
			}						
			self::cerrarConexion($conn);								
			return $resultado;
		}
		
		// Obtiene el numero total de mensajes de un usuario determinado
		static function getNumMensajesDe ($idUser)
		{				
			$conn = self::abrirConexion();		
			$count = $conn->query("SELECT count(*) as Total FROM comentarios WHERE idUser='" . $idUser . "'");
			$total = $count->fetch_object()->Total;									
			self::cerrarConexion($conn);								
			return $total;
		}
		
		// Obtiene todos los mensajes
		static function getMensajes ($pagina)
		{				
			$conn = self::abrirConexion();			
			//$select = "SELECT * FROM comentarios";
			
			$select = "SELECT * FROM comentarios LIMIT 3 OFFSET " . (3 * ($pagina - 1));
			
			$result = $conn->query($select);
			$resultado = array();
						
			while ($obj  = mysqli_fetch_object($result))
			{
				$mensaje = new Mensaje($obj->id, $obj->idUser, $obj->titulo, $obj->mensaje, $obj->fecha);				
				array_push($resultado, $mensaje);
			}						
			self::cerrarConexion($conn);								
			return $resultado;
		}
		
		// Obtiene el numero total de mensajes
		static function getNumMensajes ()
		{				
			$conn = self::abrirConexion();		
			$count = $conn->query("SELECT count(*) as Total FROM comentarios");;
			$total = $count->fetch_object()->Total;									
			self::cerrarConexion($conn);								
			return $total;
		}
		
		// Obtiene todos los mensajes tras filtrar por diferentes campos
		static function getMensajesFiltrados ($alias, $contenido, $inicio, $fin, $pagina)
		{				
			$conn = self::abrirConexion();
			$filter = "SELECT * FROM comentarios LIMIT 3 OFFSET " . (3 * ($pagina - 1)) . " WHERE 1=1 ";	
					
			if ($alias != ""){
				$email = self::getUsuarioPorAlias($alias)->get_email();
				$filter .= " AND idUser = ". chr(34) . $email . chr(34);
			}
			if ($contenido != ""){
				$filter .= " AND titulo LIKE " . chr(34) . "%". $contenido . "%" . chr(34) . " OR mensaje LIKE " . chr(34) . "%". $contenido . "%" . chr(34);
			}
			if ($inicio != ""){
				$inicio = str_replace("-", "", $inicio);
				$filter .= " AND fecha >= " . $inicio;
			}
			if ($fin != ""){
				$fin = str_replace("-", "", $fin);
				$filter .= " AND fecha <= " . $fin;
			}	
			$result = $conn->query($filter);					
			$resultado = array();						
			while ($obj  = mysqli_fetch_object($result))
			{
				$mensaje = new Mensaje($obj->id, $obj->idUser, $obj->titulo, $obj->mensaje, $obj->fecha);				
				array_push($resultado, $mensaje);
			}						
			self::cerrarConexion($conn);								
			return $resultado;
		}
		
		// Obtiene el numero total de mensajes filtrados
		static function getNumMensajesFiltrados ($alias, $contenido, $inicio, $fin)
		{
			$conn = self::abrirConexion();
			$filter = "SELECT count(*) as Total FROM comentarios WHERE 1=1 ";						
			if ($alias != ""){
				$email = self::getUsuarioPorAlias($alias)->get_email();
				$filter .= " AND idUser = ". chr(34) . $email . chr(34);
			}
			if ($contenido != ""){
				$filter .= " AND titulo LIKE " . chr(34) . "%". $contenido . "%" . chr(34) . " OR mensaje LIKE " . chr(34) . "%". $contenido . "%" . chr(34);
			}
			if ($inicio != ""){
				$inicio = str_replace("-", "", $inicio);
				$filter .= " AND fecha >= " . $inicio;
			}
			if ($fin != ""){
				$fin = str_replace("-", "", $fin);
				$filter .= " AND fecha <= " . $fin;
			}	
			$result = $conn->query($filter);	
			$total = $count->fetch_object()->Total;					
			self::cerrarConexion($conn);								
			return $total;
		}
	}
?>