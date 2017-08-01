<?php 
	$pagina = (isset($_GET["pagina"])) ? $_GET["pagina"] : 1 ;
	$web = strrchr($_SERVER["PHP_SELF"], "/");
	$autor = ($web == "/misMensajes.php");
	$web = str_replace("/", "", $web);
	if($autor)
	{
		$mensajes = BaseDatos::getMensajesDe($persona->get_email(), $pagina);
		$total = BaseDatos::getNumMensajesDe($persona->get_email());
		$admin = true;
	}
	else
	{
		$mensajes = (isset($_GET["filtrar"])) ? BaseDatos::getMensajesFiltrados($_GET["userFiltrado"], $_GET["contenido"], $_GET["inicio"], $_GET["fin"], $pagina) : BaseDatos::getMensajes($pagina);
		$total = (isset($_GET["filtrar"])) ? BaseDatos::getNumMensajesFiltrados($_GET["userFiltrado"], $_GET["contenido"], $_GET["inicio"], $_GET["fin"]) : BaseDatos::getNumMensajes();	
	}
	
	if(count($mensajes) == 0)
	{
		header("location: " . $web . "?pagina=". ($pagina - 1));
	}
	
	require "includes/paginacion.inc";
	
	echo "<div class='mensajes'>";
	foreach($mensajes as $mensaje)
	{
		$escritor = BaseDatos::getUsuario($mensaje->get_user());
		echo 
		"
			<div class='row miMensaje' style='border: 3px dotted " . $escritor->get_color() . "'>
				<h4><u>" . $mensaje->get_titulo() . "</u></h4>
				<p class='mensaje text-justify'>" . $mensaje->get_mensaje() . "</p>
				<div class='pieMensaje'>
					<div class='col-sm-3'>" . $mensaje->get_fecha() . "</div>
					<div class='col-sm-6'>
		";
		if($admin)
		{
			echo
			"					
						<button class='btn btn-default' onClick=" . chr(34) . "borrarMensaje('" . $mensaje->get_user() . "', " . $mensaje->get_id() . ", " . $pagina . ")" . chr(34) . ">Eliminar mensaje</button>
			";					
		}
		echo
		"
					</div>
					<div class='col-sm-3'>
		"; 
		echo ($autor) ? "<button class='btn btn-default' onClick=" . chr(34) . "exportarMensajePDF(" . $mensaje->get_id() . ")" . chr(34) . ">Exportar a PDF</button>" : $escritor->get_alias() ;
		echo 
		"			</div>
				</div>
			</div>
		";
	}
	echo "</div>";
?>    