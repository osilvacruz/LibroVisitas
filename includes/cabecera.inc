<?php 
	$pagina = strrchr($_SERVER["PHP_SELF"], "/");
	$mmActive = ($pagina == "/misMensajes.php") ? "active" : "" ;
	$mcActive = ($pagina == "/cuenta.php") ? "active" : "" ;
	$admActive = ($pagina == "/usuarios.php") ? "active" : "" ;		
	$logueado = isset($_SESSION["persona"]);
?>

<!-- CABECERA -->
<div class="jumbotron">
    <h1>LIBRO DE VISITAS</h1> 
</div>
<nav class="navbar navbar-inverse">
    <div class="container-fluid">
        <div class="navbar-header">
            <a class="navbar-brand" href="zonaprivada.php">LIBRO</a>
        </div>
        <?php
			if($logueado)
            {
				echo
				"
            	<ul class='nav navbar-nav'>
					<li class='" . $mmActive . "'><a href='misMensajes.php'>Mis mensajes</a></li>
					<li class='" . $mcActive . "'><a href='cuenta.php'>Mi cuenta</a></li>
				";
				if($admin)
				{
					echo
					"
					<li class='dropdown '" . $admActive . ">
						<a class='dropdown-toggle' data-toggle='dropdown' href='#'>Administración<span class='caret'></span></a>
						<ul class='dropdown-menu'>
							<li><a href='usuarios.php'>Usuarios</a></li>
							<li><a href='#'>Log</a></li>
							<li><a href='#'>Estadísticas</a></li>
						</ul>
					</li>
					";
				}
				echo 
				"
				</ul> 
				";
           	}
		?>        
        <ul class="nav navbar-nav navbar-right">
        <?php
            if($logueado)
            {
				echo
				"
            	<li><a>Hola, " . $persona->get_alias() . " </a></li>
            	<li><a href='logout.php'><span class='glyphicon glyphicon-log-out'></span> Salir</a></li> 
				";
           	}
			else
			{
				echo
				"
				<li><a>Hola, Invitado </a></li>
  				<li><a href='#' data-toggle='modal' data-target='#modalSign'><span class='glyphicon glyphicon-user'></span> Registrarse</a></li>
				<li><a href='#' data-toggle='modal' data-target='#modalLogin'><span class='glyphicon glyphicon-log-in'></span> Entrar</a></li>
  				";
			}            
		?>
        </ul>
    </div>
</nav>
