FROM_BACKUP_PATH=$1
TO_BACKUP_PATH=$2
DATE_START_BACKUP=`date '+%d/%m/%Y'`
DATE_START_BACKUP_FILE_NAME=`date '+%d_%m_%Y'`
TIME_START_BACKUP=`date '+%T'`

write_log() {
    DATE_START_LOG="Execução do backup - $DATE_START_BACKUP"
    TIME_START_LOG="Horário de início - $TIME_START_BACKUP"
    FILES_LOG="Arquivos compactados: \n$COMPRESSED_FILES"
    BACKUP_PATH_LOG="Diretório de backup: $TO_BACKUP_PATH"
    DATE_END_LOG="Horário da finalização - `date '+%T'`"

    LOG="$DATE_START_LOG\n$TIME_START_LOG\n$FILES_LOG\n$BACKUP_PATH_LOG\n$DATE_END_LOG\n"
    printf "$LOG" > $TO_BACKUP_PATH/logBKP
}

compress_path() {
    COMPRESSED_FILES=`tar -jcvf $TO_BACKUP_PATH/$BACKUP_FILE $FROM_BACKUP_PATH`
    write_log
    echo "Backup realizado com sucesso!"
}

print_invalid_path() {
    if [ -e $2 && $2 != "" ];then
        printf "O caminho $1 informado é um arquivo. Para realizar o backup, informe um caminho para um diretório.\nExemplo: /Documents/Unisinos/SistemasOperacionais\n"
    else
        echo "O diretório $1 não existe!"
    fi
}

if [[ ! -d $FROM_BACKUP_PATH || $FROM_BACKUP_PATH = "" ]];then
    print_invalid_path "origem" $FROM_BACKUP_PATH
elif [[ ! -d $TO_BACKUP_PATH || $TO_BACKUP_PATH = "" ]];then
    print_invalid_path "destino" $TO_BACKUP_PATH
else
    BACKUP_FILE=backup_$DATE_START_BACKUP_FILE_NAME.tgz
    
    if [ -e $TO_BACKUP_PATH/$BACKUP_FILE ];then
        echo "Já existe um backup com a data atual no diretório destino informado. Deseja sobrescrever esse arquivo?[s/n]"
        read CONTINUE

        if [[ $CONTINUE = "s" || $CONTINUE = "S" ]];then
            compress_path
        else
            echo "Backup cancelado!"
        fi
    else
        compress_path
    fi

fi
