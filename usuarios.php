<?php 	
	require "includes/usuario.inc";
	require "includes/BaseDatos.inc"; 
	
	session_start();
?>

<!doctype html>

<html>

<head>
    <title>Zona privada</title>
    <?php require "includes/bootstrap.html"; ?>
    <link rel="stylesheet" type="text/css" href="style/miestilo.css">
</head>

<body>

	<?php 		
		// ACCESO DENEGADO
		if(!isset($_SESSION["persona"]))
		{
			header("location: index.php");
		}
		
		// ACCESO CONCEDIDO
		$persona = $_SESSION["persona"];
		$admin = ($persona->get_email() == "admin@librovisitas.com");
		
		// NO ES EL ADMINISTRADOR
		if(!$admin)
		{
			header("location: index.php");
		}		
	?>

	<div class="container text-center">
    
        <!-- CABECERA -->
        <?php require "includes/cabecera.inc"; ?>
      
        <!-- USUARIOS -->
        <?php require "includes/usuarios.inc"; ?>
        
        <!-- PIE DE PÁGINA -->
     	<?php require "includes/pie.inc"; ?>
      
    </div>
    
    <script>
		function borrarMensaje (user, id)
		{
			if(confirm("¿Realmente desea borrar el mensaje de '" + user + "' ?"))
			{
				location = "zonaprivada.php?mensajeElim=" + id;	
			}		
		}
	</script>  
    
</body>

</html>