-- selecionar a base de dados
USE driveIt;

-- Querie 0: Lista de todas as aulas
Select * From aula;

-- Querie 1: Lista de slots das aulas livres com info relevante, sem identificar o nome do instrutor
Select Data, Hora, Estado, Instrutor_id AS `ID do Instrutor` From aula
    where Estado IN ('L');
    
    
-- Querie 2: Lista de slots das aulas livres com info relevante, indentificando o nome do instrutor
Select Instrutor_id AS `ID do Instrutor`, Instrutor.Nome AS `Nome do Instrutor`, Data, Hora, Estado  From aula
	JOIN Instrutor ON Instrutor.id = aula.Instrutor_id
		where Estado IN ('L');


-- Querie 3: Lista de aulas marcadas por Aluno, ordenados ascendentemente pelo nome do aluno (mostra morada também)
Select aula.id AS `ID da Aula`, Aluno.id AS `ID do Aluno`, Aluno.Nome, aula.Data, aula.Hora, 
	aula.Carro_Matricula AS `Matrícula do Carro`, aula.Instrutor_id AS `ID do Instrutor`, Morada.Rua, Morada.Localidade, 
    Morada.`Código-Postal` FROM Aluno
    JOIN aula ON Aluno.id = aula.Aluno_id
    JOIN Morada ON Morada.idMorada = Aluno.Morada_idMorada
        order by Aluno.Nome ASC;
        
    
-- Querie 4: Lista de alunos com pagamentos em FALTA (mostra morada)
Select Pagamento AS `Estado de Pagamento`, id AS `ID do Aluno`, Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, 
	Nrº_CC AS `Nº de CC`, NIF, Morada.Rua, Morada.Localidade, Morada.`Código-Postal` From Aluno
    JOIN Morada ON Morada.idMorada = Aluno.Morada_idMorada
		where Aluno.Pagamento = 'N'
		order by Nome ASC;
    

-- Querie 5: Lista de alunos com pagamentos FEITOS (mostra morada)
Select Pagamento AS `Estado de Pagamento`, id AS `ID do Aluno`, Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, 
	Nrº_CC AS `Nº de CC`, NIF, Morada.Rua, Morada.Localidade, Morada.`Código-Postal` From Aluno
    JOIN Morada ON Morada.idMorada = Aluno.Morada_idMorada
		where Aluno.Pagamento = 'S'
		order by Nome ASC;

        
-- Querie 6: Lista de aulas dadas por instrutor
Select aula.id AS `ID da aula`, instrutor.id AS `ID do Instrutor`, Nome, Email, Nrº_Telemóvel, aula.Data, aula.Hora, 
	aula.Carro_Matricula, aula.Aluno_id FROM instrutor
	JOIN aula ON instrutor.id = aula.Instrutor_id
			where aula.Estado = 'M'
			order by instrutor.Nome;
        
        
-- Querie 7: Ranking de funcionário, consoante as aulas com que interagiu (exclui-se as que estão livres) por ordem
-- decrescente
Select Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, count(Funcionario.id) AS `Total de Aulas` From Funcionario
	JOIN aula ON aula.Funcionario_id = Funcionario.id
		where aula.Estado IN ('M','D','R')
		group by Funcionario.id
		order by `Total de Aulas` DESC;


-- Querie 8: Ranking de instrutor, consoante as aulas dadas (contabiliza também as que estão a decorrer, caso 
-- algum esteja durante uma aula
Select Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, count(Instrutor.id) AS `Total de Aulas` From Instrutor
	JOIN aula ON aula.Instrutor_id = Instrutor.id
		-- escolher se é só realizadas ou a decorrer também
		where aula.Estado IN ('R','D')
		group by Instrutor.id
		order by `Total de Aulas` DESC;
        
        
-- Querie 9: Ranking de carros, consoante as aulas em que foram utilizados
Select Matricula, count(Carro.Matricula) AS `Total de Aulas` From Carro
	JOIN aula ON aula.Carro_matricula = Carro.Matricula
		-- escolher se é só realizadas ou a decorrer também
		where aula.Estado IN ('R','D')
        group by Carro.Matricula
        order by `Total de Aulas` DESC;
        
        
-- Querie 10: Lista de alunos na nossa base de dados, com a sua morada, ordenados ascendentemente pelo nome
Select Aluno.id AS `ID do Aluno`, Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, Nrº_CC AS `Nº de CC`, NIF, Pagamento, 
	Morada.Rua, Morada.Localidade, Morada.`Código-Postal` From Aluno
    JOIN Morada ON Morada.idMorada = Aluno.Morada_idMorada
		order by Nome ASC;
        
    
-- Querie 11: Lista de funcionários com a sua morada, ordenados ascendentemente pelo nome
Select Funcionario.id AS `ID do Funcionário`, Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, Nrº_CC AS `Nº de CC`, 
	Morada.Rua, Morada.Localidade, Morada.`Código-Postal` From Funcionario
    JOIN Morada ON Morada.idMorada = Funcionario.Morada_idMorada
		order by Nome ASC;
    
    
-- Querie 12: Lista de instrutores com a sua morada
Select Instrutor.id AS `ID do Instrutor`, Nome, Email, Nrº_Telemóvel AS `Nº de Telemóvel`, Nrº_CC AS `Nº de CC`, Morada.Rua,
	Morada.Localidade, Morada.`Código-Postal` From Instrutor
    JOIN Morada ON Morada.idMorada = Instrutor.Morada_idMorada
		order by Nome ASC;
    

-- Querie 13: Listagem das aulas todas realizadas, identificando pelo aluno
SELECT aula.id AS `ID da aula`, Data, Hora, Estado AS `Estado da Aula`, Carro_Matricula, 
	Instrutor.Nome AS `Nome do Instrutor`, Aluno.Nome AS `Nome do Aluno`, Aluno.Email FROM aula
	JOIN Aluno ON Aluno.id = aula.Aluno_id
    JOIN Instrutor ON Instrutor.id = aula.Instrutor_id
		where Estado IN ('R')
		order by Aluno.Nome;
        
        
-- Querie 14: Exemplo de uma atualização de uma aula, passar para 'realizada'. Só passa para realizada se o estado
-- for a decorrer e os dados introduzidos derem match
-- Se for preciso apagar a procedure: 
DROP PROCEDURE update_aula_realizada;
delimiter //
CREATE PROCEDURE update_aula_realizada (IN idInstrutor INT, idAula INT)
       BEGIN
        Update aula
			Set Estado = 'R'
			-- é dado o estado da aula, id do Instrutor, o dia e a hora da aula
			where Estado = 'D' AND aula.id = idAula;
       END//
delimiter ;


-- Querie 15: Exemplo de um cancelamento de uma aula, passar para 'livre'. Só passa para livre se o estado
-- for de marcada e os dados introduzidos derem match
-- Se for preciso apagar a procedure: 
DROP PROCEDURE cancelar_aula;
delimiter //
CREATE PROCEDURE cancelar_aula (IN idFuncionario INT, idAula INT)
       BEGIN
        Update aula
			-- atualiza slot para Livre
            -- atualiza a matricula do carro para null
            -- apaga o funcionário
            -- apaga o id do aluno
			Set Estado = 'L', Carro_Matricula = null, Funcionario_id = null, Aluno_id = null
            -- Aluno_id = 0, 
				-- é dado o estado da aula, id do Funcionario (só funcionários é que cancelam aulas) e o id da aula
				where aula.Estado = 'M' AND aula.id = idAula AND aula.Funcionario_id = idFuncionario;
       END//
delimiter ;


-- Querie 16: Exemplo de uma marcação de aula, passar para 'marcada'. Só passa para marcada se o estado
-- for a livre e os dados introduzidos derem match
-- Se for preciso apagar a procedure: 
DROP PROCEDURE marcar_aula;
delimiter //
CREATE PROCEDURE marcar_aula (IN idAula INT, idFuncionario INT, idAluno INT, matricula VARCHAR(45))
       BEGIN
		Update aula
			Set Estado = 'M', `Carro_Matricula` = matricula, Funcionario_Id = idFuncionario, Aluno_id = idAluno
			-- é dado o id do aluno, o dia, hora da aula e confirmar que se tratava de uma aula a decorrer
			where Estado = 'L' AND aula.id = idAula;
       END//
delimiter ;

CALL marcar_aula(1,1,1,"QA-18-QL");


-- Querie 17: Marcar slots de todas as aulas de um instrutor para um dia
DROP PROCEDURE marcar_slots_aula;
delimiter //
CREATE PROCEDURE marcar_slots_aula (IN idInstrutor INT, dataC DATE)
       BEGIN
		INSERT INTO aula (`Data`,`Hora`,`Estado`,`Instrutor_Id`)
			VALUES  
				(dataC,"10:00:00","L",idInstrutor),
				(dataC,"11:00:00","L",idInstrutor),    
				(dataC,"15:00:00","L",idInstrutor),                    
				(dataC,"16:00:00","L",idInstrutor),           
				(dataC,"17:00:00","L",idInstrutor);
       END//
delimiter ;

CALL marcar_slots_aula(1, date(now()));


-- Querie 18: Verificar todas as aula no dia atual (utilizando views)
CREATE VIEW vwAulasHoje AS
Select * from aula
	where Data = date(now());
    
Select * from vwAulasHoje;

-- Querie 19: Retorna o nome de um instrutor dado o id dele (FUNCTION)
DROP FUNCTION nomeInstrutor; 
delimiter //
CREATE FUNCTION `nomeInstrutor` (idInstrutor int)
	returns VARCHAR(45)
    READS SQL DATA
	DETERMINISTIC
    Begin
		declare nomeInstrutor VARCHAR(45);
        set nomeInstrutor = (select Nome from Instrutor where id = idInstrutor);
        return nomeInstrutor;
	End//
 
Select nomeInstrutor(1);

-- Querie 20: A cada instrutor, inserir aulas dele do dia de hoje. Não funciona!
delimiter //
CREATE TRIGGER inserir_aulas AFTER INSERT ON Instrutor
FOR EACH ROW
BEGIN
     CALL marcar_slots_aula(NEW.id, date(now()));
END;
delimiter ;
