import { AiOutlineClose } from "react-icons/ai";
import "./styles/history.css";
import { DeleteMethod } from "@/utils/RestMethods";
import { toast } from "react-toastify";

export const PATH = "path";
export const FILTER = "Filter";
export const KEYWORD = "keyword";

interface Props {
    items: Array<any>,
    endpoint: string,
    updateDefaultValue: (value: any) => void,
};

export const History = (props: Props): JSX.Element => {
    const {
        items,
        endpoint,
        updateDefaultValue,
    } = props;

    const deleteHistoryOption = (param: any): void => {
		const params = JSON.stringify(param);

		DeleteMethod(`http://localhost:8080/api/v1/${endpoint}`, params, (status: number, response: any) => {
			if (status === 202) {
				toast("Item do histórico deletado com sucesso!");
			}

			if (status >= 400) {
				const error = "Error: " + response.error,
					msg = "Message: " + response.message;
				console.error(error);
				console.error(msg);

				toast("Ocorreu um erro ao deletar o item do histórico.");
			}
		});
	};

    return (
        <div className="history">
            {
                items.map((item: any, index: number) => (
                    <div key={index}>
                        <p defaultValue={item.path} onClick={() => updateDefaultValue(item)}>
                            {item.path}
                        </p>
                        <button onClick={() => deleteHistoryOption(item)}>
                            <AiOutlineClose />
                        </button>
                    </div>
                ))
            }
        </div>
    );
};