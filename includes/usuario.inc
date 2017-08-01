<?php	
	class Usuario
	{
		private $email, $pwd, $alias, $nombre, $color, $errores;
		
		function __construct($correo, $password, $user, $name, $colour, $fallos)
		{
			$this->email = $correo;			
			$this->pwd = $password;
			$this->alias = $user;
			$this->nombre = $name;
			$this->color = $colour;
			$this->errores = $fallos;
		}
		
		function get_email()
		{
			return $this->email;
		}
		
		function get_password()
		{
			return $this->pwd;
		}
		
		function get_alias()
		{
			return $this->alias;
		}			
		
		function get_nombre()
		{
			return $this->nombre;
		}
		
		function get_color()
		{
			return $this->color;
		}
		
		function get_errores()
		{
			return $this->errores;
		}
		
		function set_errores($fallos)
		{
			$this->errores = $fallos;
		}	
	}
	
	class Mensaje
	{
		private $id, $idUser, $titulo, $mensaje, $fecha;
		
		function __construct($id, $idUser, $titulo, $mensaje, $fecha)
		{	
			$this->id = $id;	
			$this->idUser = $idUser;
			$this->titulo = $titulo;
			$this->mensaje = $mensaje;
			$this->fecha = $fecha;
		}
		
		function get_id()
		{
			return $this->id;
		}
		
		function set_id($id)
		{
			$this->id = $id;
		}
		
		function get_user()
		{
			return $this->idUser;
		}
		
		function set_user($idUser)
		{
			$this->idUser = $idUser;
		}
		
		function get_titulo()
		{
			return $this->titulo;
		}
			
		function set_titulo($titulo)
		{
			$this->titulo = $titulo;
		}		
		
		function get_mensaje()
		{
			return $this->mensaje;
		}	
		
		function set_mensaje($mensaje)
		{
			$this->mensaje = $mensaje;
		}
		
		function get_fecha()
		{
			return $this->fecha;
		}
		
		function set_fecha($fecha)
		{
			$this->fecha = $fecha;
		}
	}
?>