<?php	
	require "includes/usuario.inc";
	require "includes/BaseDatos.inc"; 
	require 'includes/encriptacion.inc';
	
	session_start();
?>

<!doctype html>

<html>

<head>
    <title>Acceso</title>
    <?php require "includes/bootstrap.html"; ?>
</head>

<body> 
	<?php 
		// USUARIO LOGUEADO
		if(isset($_SESSION["persona"]))
		{
			header("location: zonaprivada.php");
		}
		
        // USUARIO BLOQUEADO
        if(isset($_GET["usuario"]))
        {
            echo "<script>alert('Usuario " . $_GET["usuario"] . " bloqueado. Pongase en contacto con el administrador');</script>";	
        }
        // SE QUITA EL POSIBLE FILTRADO
        if(isset($_GET["mostrarTodo"]))
        {
            header("location: index.php");
        }		
        $filtrado = isset($_GET["filtrar"]);
        $admin = isset($_SESSION["persona"]);
    ?> 
    
	<div class="container text-center">
    
		<!-- CABECERA -->
        <?php require "includes/cabecera.inc"; ?>
      
        <!-- VENTANA MODAL DE LOGIN -->
        <?php require "includes/modalLogin.inc"; ?>
        
        <!-- VENTANA MODAL DE SIGN UP -->
        <?php require "includes/modalSign.inc"; ?>
      
		<!-- FILTRADO -->
		<?php require "includes/filtro.inc"; ?>
           
        <!-- MENSAJES -->
        <?php require "includes/mensajes.inc"; ?> 
        
        <!-- PIE DE PÁGINA -->
        <?php require "includes/pie.inc"; ?>
	
    </div>
    
    <!-- ACCIONES DE FORMULARIO -->
	<?php		
		// REGISTRO
		if(isset($_POST["registrar"]))
		{
			$errorRegistro = 0;
			$email = $_POST["emailSign"];
			$alias = $_POST["aliasSign"];
			filter_var($email, FILTER_VALIDATE_EMAIL);			
			// Si el email ya existe
			if(BaseDatos::getUsuario($email) != NULL)
			{
				echo "<script>alert('El email ya existe');</script>";
				echo "<script>$('#modalLogin').modal('show');</script>";					
			}
			else
			{
				// Si el alias ya existe
				if(BaseDatos::getUsuarioPorAlias($alias) != NULL)
				{
					echo "<script>alert('El alias ya existe');</script>";
					echo "<script>$('#modalSign').modal('show');</script>";						
				}
				else
				{
					// Si todo es correcto se incluye como variable de sesión el nuevo usuario introducido		
					$contrasena = password_hash($_POST["pwdSign"], PASSWORD_BCRYPT, array("cost" => 10));									
					$persona = new Usuario($email, $contrasena, $alias, $_POST["nombreSign"], $_POST["colorSign"] , 0);			
					$_SESSION["persona"] = $persona;
					BaseDatos::agregarUsuario($persona);			
					header("location: zonaprivada.php");
				}
			}
		}
		
		// ACCESO
		if(isset($_POST["acceder"]))
		{
			// Se comprueba que es un usuario existente en la base de datos y que no esté bloqueado
			$persona = BaseDatos::getUsuario($_POST["emailLogin"]);	
			// Persona bloqueada
			if(($persona != NULL) and ($persona->get_errores() > 2))
			{
				header("location: index.php?usuario=" . $persona->get_email());				
			}	
			else
			{
				// Persona inexistente o contraseña incorrecta
				if(($persona == NULL) or (password_verify($persona->get_password(), $_POST["pwdLogin"])))
				{	
					echo "<script>$('#modalLogin').modal('show');</script>";							
					if($persona == NULL)
					{
						echo "<script>alert('Usuario inexistente en la base de datos');</script>";				
					}
					else
					{
						echo "<script>alert('Contraseña incorrecta');</script>";
						$persona->set_errores($persona->get_errores() + 1);
						BaseDatos::actualizarUsuario($_POST["emailLogin"], $persona);										
					}								
				}
				else
				{
					$persona->set_errores(0);
					BaseDatos::actualizarUsuario($_POST["emailLogin"], $persona);
					$_SESSION["persona"] = $persona;
					header("location: zonaprivada.php");
				}	
			}
		}
	?>
    
    <script>
	
		if(document.getElementById("mostrarTodo"))
		{
			document.getElementById("mostrarTodo").onclick = mostrarTodo;
		}
		
    	function mostrarTodo()
		{
			window.location.assign("index.php");
		}
		
    </script>
    
</body>

</html>