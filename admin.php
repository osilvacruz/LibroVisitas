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
    <style>
    	.mensajes
		{
			margin: 20px 0;
		}
		.miMensaje
		{
			margin: 10px;
			padding: 10px;
		}
		.mensaje
		{
			overflow:auto;			
		}
		.izquierda
		{
			float:left;
		}
		.derecha
		{
			float:right;
		}
    </style>
</head>

<body>

	<?php		
		// ACCESO DENEGADO (Si se intenta acceder sin sesión nos manda a la página pública, donde no se puede publicar)
		if(!isset($_SESSION["persona"]))
		{
			header("location: index.php");
		}		
		$persona = $_SESSION["persona"];
		$admin = !(($persona->get_email() != "admin@librovisitas.com") or ($persona->get_password() != "1234"));
		
		// Si es un usuario logueado permite publicar		
		if(isset($_POST["publicar"]))
		{
			$mensaje = new Mensaje(NULL, $persona->get_email(), $_POST["nuevoTitulo"], $_POST["nuevoMensaje"], NULL) ;
			BaseDatos::agregarMensaje($persona, $mensaje);
			header("location: misMensajes.php");
		}
	?>

	<div class="container text-center">
      <div class="jumbotron">
        <h1>LIBRO DE VISITAS</h1> 
      </div>
      <nav class="navbar navbar-inverse">
        <div class="container-fluid">
          <div class="navbar-header">
            <a class="navbar-brand" href="zonaprivada.php">LIBRO</a>
          </div>
          <ul class="nav navbar-nav">
            <li><a href="misMensajes.php">Mis mensajes</a></li>
            <li><a href="cuenta.php">Mi cuenta</a></li>
            <?php
				if($admin)
				{
					echo "<li class='active'><a href='admin.php'>Administración</a></li>";	
				}            	
			?>
          </ul>
          <form class="navbar-form navbar-left">
            <div class="input-group">
              <input type="text" class="form-control" placeholder="Search">
              <div class="input-group-btn">
                <button class="btn btn-default" type="submit">
                  <i class="glyphicon glyphicon-search"></i>
                </button>
              </div>
            </div>
          </form>
          <ul class="nav navbar-nav navbar-right">
            <li><a>Hola, <?php echo $persona->get_alias(); ?></a></li>
            <li><a href="index.php"><span class="glyphicon glyphicon-log-out"></span> Logout</a></li>
          </ul>
        </div>
      </nav>
      
      
      
	</div>
    
    <!-- PIE DE PÁGINA -->
    <?php require "includes/pie.inc"; ?>    
	
</body>

</html>