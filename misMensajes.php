<?php 
	require "includes/usuario.inc";	
	require "includes/BaseDatos.inc";
	
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
		// ACCESO DENEGADO (Si se intenta acceder sin sesión nos manda a la página pública, donde no se puede publicar)
		if(!isset($_SESSION["persona"]))
		{
			header("location: index.php");
		}
		// ACCESO CONCEDIDO
		$persona = $_SESSION["persona"];
		$admin = ($persona->get_email() == "admin@librovisitas.com");
		// Si es un usuario logueado permite publicar		
		if(isset($_POST["publicar"]))
		{
			$mensaje = new Mensaje(NULL, $persona->get_email(), $_POST["nuevoTitulo"], $_POST["nuevoMensaje"], NULL) ;
			BaseDatos::agregarMensaje($persona, $mensaje);
			header("location: misMensajes.php");
		}
		// Si es un usuario logueado permite eliminar sus mensajes
		if(isset($_GET["mensajeElim"]))
		{
			BaseDatos::eliminarMensaje($_GET["mensajeElim"]);
			$destino = (isset($_GET["pagina"])) ? "?pagina=" . $_GET["pagina"] : "" ;			
			header("location: misMensajes.php" . $destino);
		}
	?>

    <div class="container text-center">
        
        <!-- CABECERA -->
        <?php require "includes/cabecera.inc"; ?>
      
        <!-- NUEVO MENSAJE -->
        <?php require "includes/nuevoMensaje.inc"; ?>            
    	        
        <!-- MENSAJES DEL USUARIO LOGUEADO -->
        <div>
        	<label><?php echo $persona->get_alias(); ?> ha dicho:</label>
		</div> 
		<?php require "includes/mensajes.inc"; ?> 
        
        <!-- PIE DE PÁGINA -->
        <?php require "includes/pie.inc"; ?>  
      
	</div>
    
    <script>
		function borrarMensaje (user, id, pagina)
		{
			if(confirm("¿Realmente desea borrar el mensaje?"))
			{
				location = "misMensajes.php?mensajeElim=" + id + "&pagina=" + pagina;	
			}		
		}
		
		function exportarMensajePDF (id)
		{
			if(confirm("¿Realmente desea exportar a PDF el mensaje?"))
			{
				location = "misMensajes.php?mensajePDF=" + id;	
			}		
		}
	</script> 
    
</body>

</html>