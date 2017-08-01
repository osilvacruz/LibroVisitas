<?php 
	$pagina = $_SERVER["PHP_SELF"];
?>

<!-- NUEVO MENSAJE -->
<div class="row">
    <form method="post" action="misMensajes.php" class="col-sm-12 text-justify">
        <label for="nuevoTitulo"><?php echo $persona->get_alias(); ?> dice:</label>
        <div class="form-group">
        	<label class="sr-only" for="nuevoTitulo">Titulo:</label>        
        	<input type="text" class="form-control" id="nuevoTitulo" name="nuevoTitulo" placeholder="Introduzca el titulo de su mensaje">
        </div>
        <div class="form-group">
        	<label class="sr-only" for="nuevoMensaje">Mensaje:</label>
        	<textarea class="form-control" id="nuevoMensaje" name="nuevoMensaje" placeholder="Introduzca el mensaje que desea publicar" rows="3"></textarea>
        </div>
        <div class="form-group">
        	<button type="submit" class="btn btn-default" name="publicar">Publicar</button>
        </div>        
    </form>
</div>