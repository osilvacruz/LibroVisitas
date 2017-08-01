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
		$filtrado = isset($_GET["filtrar"]);
		
		// SE QUITA EL POSIBLE FILTRADO
        if(isset($_GET["mostrarTodo"]))
        {
            header("location: zonaprivada.php");
        }
		
		// ACCIONES DE ADMINISTRADOR
		if($admin)
		{	
			// ELIMINA MENSAJE
			if(isset($_GET["mensajeElim"]))
			{
				BaseDatos::eliminarMensaje($_GET["mensajeElim"]);
				header("location: zonaprivada.php");
			}
		}		
	?>

	<div class="container text-center">
    
        <!-- CABECERA -->
        <?php require "includes/cabecera.inc"; ?>
      
      	<!-- FILTRADO -->
		<?php require "includes/filtro.inc"; ?>
      
        <!-- MENSAJES -->
        <?php require "includes/mensajes.inc"; ?> 
        
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

		if(document.getElementById("mostrarTodo"))
		{
			document.getElementById("mostrarTodo").onclick = mostrarTodo;
		}
		
    	function mostrarTodo()
		{
			window.location.assign("zonaprivada.php");
		}		
		
	</script>  
    
</body>

</html>