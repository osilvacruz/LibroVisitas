<!-- VENTANA MODAL DE LOGIN -->
<div id="modalLogin" class="modal fade" role="dialog">
  <div class="modal-dialog">      
    <!-- CONTENIDO-->
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal">&times;</button>
        <h4 class="modal-title">ENTRAR</h4>
      </div>
      <div class="modal-body">
          <form method="post" action="index.php" onSubmit="return validarLogin()">
            <div class="form-group">
              <label for="emailLogin">Email:</label>
              <input type="email"  maxlength="80" class="form-control" id="emailLogin" name="emailLogin" value="<?php echo (isset($_POST["emailLogin"])) ? $_POST["emailLogin"] : (isset($_POST["emailSign"])) ? $_POST["emailSign"] : "" ; ?>">
            </div>
            <div class="form-group">
              <label for="pwdLogin">Contraseña:</label>
              <input type="password" maxlength="20" class="form-control" id="pwdLogin" name="pwdLogin">
            </div>
            <div class="form-group">
            	<button type="submit" class="btn btn-default" id="acceder" name="acceder" value="<?php echo (isset($_POST["pwdLogin"])) ? $_POST["pwdLogin"] : "" ; ?>">Acceder</button>
          	</div>
          </form>
      </div>
    </div>      
  </div>
</div>

<script>
	function validarLogin()
	{
		var email = document.getElementById("emailLogin").value;
		var pwd = document.getElementById("pwdLogin").value;
		var resultado = true;
		
		if((email == "") || (pwd == ""))
		{
			alert ("Los campos no pueden estar vacíos");
			resultado = false;
		}
		return resultado;
	}
</script>