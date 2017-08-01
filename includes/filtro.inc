<div class="jumbotron text-left">
	<form class="row" method="get" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
    	<div class="col-sm-2">
            <label for="userFiltrado">Usuario:</label>
            <select class="form-control" name="userFiltrado" id="userFiltrado">
                <option value=""></option>;
                <?php 
                    foreach(Basedatos::getUsuarios() as $usuario)
                    {
						$alias = $usuario->get_alias();						
						$selected = ($alias == $_GET["userFiltrado"]) ? "selected" : "" ;
                        echo 
						"
						<option " . $selected . " value='" . $alias . "'>" . $alias . "</option>
						";
                    }
                ?>
			</select>                
        </div>
        <div class="col-sm-2">
            <label for="contenido">Contenido:</label>
            <input type="text" class="form-control" id="contenido" name="contenido" value="<?php echo ($filtrado) ? $_GET["contenido"] : "" ; ?>">
        </div>
        <div class="col-sm-3">
            <label for="inicio">Fecha inicio:</label>
            <input type="date" class="form-control" id="inicio" name="inicio" value="<?php echo ($filtrado) ? $_GET["inicio"] : "" ; ?>">
        </div>
        <div class="col-sm-3">
            <label for="fin">Fecha fin:</label>
            <input type="date" class="form-control" id="fin" name="fin" value="<?php echo ($filtrado) ? $_GET["fin"] : "" ; ?>">
        </div>
        <div class="col-sm-2">
        	<label for="filtrar">Acciones:</label><br>
            <button type='submit' class='btn btn-default' id='filtrar' name='filtrar'><span class="glyphicon glyphicon-filter"></span></button>  
            <button type="button" <?php echo ($filtrado) ? "" : "disabled" ; ?> class="btn btn-default" id="mostrarTodo"><span class="glyphicon glyphicon-refresh"></span></button>
        	<button type="submit" class="btn btn-default" id="filtrar" name="filtrar"><span class="fa fa-file-pdf-o"></span></button>
        </div>        
    </form>          
</div>