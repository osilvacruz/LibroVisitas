<?php 	
	$paginas = floor($total / 3);
	if($total % 3 != 0)
	{
		$paginas++;
	}	
	$limite = 2;
	$primera = 1;
	$ultima = $paginas;
	if($paginas > $limite)
	{
		$primera = min($paginas - $limite + 1, $pagina);
		$ultima = min($primera + $limite - 1, $paginas);
	}
	
	echo "<ul class='pagination text-center'>";	
	if($paginas > $limite)
	{
		$disabled = ($pagina == 1) ? "class='disabled'" : "";
		echo "<li " . $disabled . "><a href='" . $web . "?pagina=" . (string)(max(1 ,$pagina - 1)) . "'> < </a></li>";	
	}	
	for($x = $primera ; $x <= $ultima ; $x++)
	{
		$activo = ($x == $pagina) ? "class='active'" : "";			
		echo "<li " . $activo . "><a href='" . $web . "?pagina=" . $x . "'>" . $x . "</a></li>";
	}		
	if($paginas > $limite)
	{
		$disabled = ($pagina == $paginas) ? "class='disabled'" : "";
		echo "<li " . $disabled . "><a href='" . $web . "?pagina=" . (string)(min($paginas ,$pagina + 1)) . "'> > </a></li>";	
	}
	echo "</ul>";	
?>

