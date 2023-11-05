import { useState, useEffect } from "react";
import { PostMethod } from "@/utils/RestMethods";
import { toast } from "react-toastify";
import "./styles/panel.css";

export interface Line {
	num: number;
	content: string;
};

export interface File {
	path: string;
	lines: Line[];
};

interface Props {
	params: any,
	submit: () => void,
	cleanAll: () => void
};

export const Panel = (props: Props): JSX.Element => {
	const { params, submit, cleanAll } = props;
	const [files, setFiles] = useState<File[]>([]);
	const [lines, setLines] = useState<Line[]>([]);

	const search = (): void => {
		submit();

		PostMethod("http://localhost:8080/api/v1/Search/find", JSON.stringify(params), (status: number, response: any) => {
			if (status === 200) {
				setFiles(response.results);
			}

			if (status >= 400) {
				const error = "Error: " + response.error,
					msg = "Message: " + response.message;
				console.error(error);
				console.error(msg);

				toast("Ocorreu um erro ao realizar a pesquisa.");
			}
		});
	};

	return (
		<>
			<button className="search-button" onClick={search}>Pesquisar</button>
			<button className="clean-button" onClick={cleanAll}>Limpar</button>

			<div className="results-panel">
				<div className="panel" id="files">
				{
					files.length > 0 &&
					files.map((item: File, index: number) => (
						<div key={index}>
							<p onClick={() => setLines(item.lines)}>{item.path}</p>
						</div>
					))
				}
				</div>

				<span></span>
				
				<div className="panel" id="lines">
				{
					lines.length > 0 &&
					lines.map((item: Line, index: number) => (
						<div key={index}>
							<p>Linha {item.num}: {item.content}</p>
						</div>
					))
				}
				</div>
			</div>
		</>
	);
};
