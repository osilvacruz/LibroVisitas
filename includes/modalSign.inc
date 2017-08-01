<?php

?>

<!-- VENTANA MODAL DE LOGIN -->
<div id="modalSign" class="modal fade" role="dialog">
    <div class="modal-dialog">      
        <!-- CONTENIDO-->
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">REGISTRO</h4>
            </div>
            <div class="modal-body">
                <form method="post" action="index.php" onSubmit="return validarSign()">
                    <div class="form-group">
                        <label for="emailSign">Email:</label>
                        <input type="email" maxlength="80" class="form-control" id="emailSign" name="emailSign" value="<?php echo (isset($_POST["emailSign"])) ? $_POST["emailSign"] : "" ; ?>">
                    </div>
                    <div class="form-group">
                        <label for="pwdSign">Contraseña:</label>
                        <input type="password" maxlength="20" class="form-control" id="pwdSign" name="pwdSign" value="<?php echo (isset($_POST["pwdSign"])) ? $_POST["pwdSign"] : "" ; ?>">
                    </div>
                    <div class="form-group">
                        <label for="aliasSign">Alias:</label>
                        <input type="text" maxlength="40" class="form-control" id="aliasSign" name="aliasSign" value="<?php echo (isset($_POST["aliasSign"])) ? $_POST["aliasSign"] : "" ; ?>">
                    </div>
                    <div class="form-group">
                        <label for="nombreSign">Nombre completo:</label>
                        <input type="text" maxlength="256" class="form-control" id="nombreSign" name="nombreSign" value="<?php echo (isset($_POST["nombreSign"])) ? $_POST["nombreSign"] : "" ; ?>">
                    </div>
                    <div class="form-group">
                        <label for="color">Color representativo:</label>
                        <input type="color" class="form-control" id="colorSign" name="colorSign" value="<?php echo (isset($_POST["colorSign"])) ? $_POST["colorSign"] : "" ; ?>">
                    </div>
                    <button type="submit" class="btn btn-default" name="registrar">Registrarme</button>
                </form>
            </div>
        </div>      
    </div>
</div>

<script>
function validarSign()
{
	var email = document.getElementById("emailSign").value;
	var pwd = document.getElementById("pwdSign").value;
	var alias = document.getElementById("aliasSign").value;
	var nombre = document.getElementById("nombreSign").value;
	var color = document.getElementById("colorSign").value;
	var resultado = true;
	
	if((email == "") || (pwd == "") || (alias == "") || (nombre == "") || (color == ""))
	{
		alert ("Todos los campos deben tener valor");
		resultado = false;
	}
	return resultado;
}
</script>