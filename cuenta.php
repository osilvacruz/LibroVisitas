<?php 
	require "includes/usuario.inc";	
	require "includes/BaseDatos.inc";
	require 'includes/encriptacion.inc';
	session_start(); 
?>

<!doctype html>

<html>

<head>
    <title>Mi cuenta</title>
    <?php require "includes/bootstrap.html"; ?>
</head>

<body>
	<?php		
		// ACCESO DENEGADO
		if(!isset($_SESSION["persona"]))
		{
			header("location: index.php");
		}
		
		// ACCESO VALIDADO -> SE INICIA UNA SESION
		$persona = $_SESSION["persona"];
		$admin = ($persona->get_email() == "admin@librovisitas.com");
		
		// ACTUALIZACIÓN DE DATOS
		if(isset($_POST["actualizar"]))
		{
			$contrasena = ($_POST["miPwd"] == "") ? $persona->get_password() :  password_hash($_POST["miPwd"], PASSWORD_BCRYPT, array("cost" => 10));			
			$nuevaPersona = new Usuario($_POST["miEmail"], $contrasena, $_POST["miAlias"], $_POST["miNombre"], $_POST["miColor"], 0);
			$_SESSION["persona"] = $nuevaPersona;
			BaseDatos::actualizarUsuario($persona->get_email(), $nuevaPersona);
			header("location: cuenta.php");
		}
		
		// ELIMINACIÓN DE CUENTA 
		if(isset($_GET["eliminar"]))
		{
			BaseDatos::eliminarUsuario($persona->get_email());
			header("location: logout.php");
		}
	?>

	<div class="container text-center">
    
		<!-- CABECERA -->
        <?php require "includes/cabecera.inc"; ?>	
      
      <!-- DATOS -->
     <div class="row">
      	<div class="col-sm-3"></div>
      	<form method="post" action="cuenta.php" class="col-sm-6">
          <div class="form-group">
            <label for="miEmail">Email:</label>
            <input type="email" readonly class="form-control text-center" id="miEmail" name="miEmail" value="<?php echo $persona->get_email(); ?>">
          </div>
          <div class="form-group">
            <label for="miPwd">Contraseña:</label>
            <input type="text" maxlength="20" class="form-control text-center" id="miPwd" name="miPwd" placeholder="Introduzca una nueva contraseña si desea cambiarla">
          </div>
          <div class="form-group">
            <label for="miAlias">Alias:</label>
            <input type="text" maxlength="40" class="form-control text-center" id="miAlias" name="miAlias" value="<?php echo $persona->get_alias(); ?>">
          </div>
          <div class="form-group">
            <label for="miNombre">Nombre completo:</label>
            <input type="text" maxlength="256" class="form-control text-center" id="miNombre" name="miNombre" value="<?php echo $persona->get_nombre(); ?>">
          </div>
          <div class="form-group">
              <label for="color">Color representativo:</label>
              <input type="color" class="form-control" id="miColor" name="miColor" value="<?php echo $persona->get_color(); ?>">
          </div>
          <div class="form-group">
              <button type="submit" class="btn btn-default" name="actualizar">Actualizar</button>
              <?php 
			  	if(!$admin)
				{
					echo "<input type='button' class='btn btn-default' id='eliminar' value='Eliminar'>";	
				}
			  ?>              
          </div>          
        </form>
        <div class="col-sm-3"></div>
      </div>
     <!-- PIE DE PÁGINA -->
    <?php require "includes/pie.inc"; ?> 
     
    </div>	
    
    <script>
		if(document.getElementById("eliminar"))
		{
			document.getElementById("eliminar").onclick = borrarUsuario;	
		}		
		
		function borrarUsuario ()
		{
			if(confirm("Realmente desea borrar su cuenta"))
			{
				location = "cuenta.php?eliminar=true";	
			}		
		}
	</script>
</body>

</html>