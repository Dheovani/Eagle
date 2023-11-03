import { useState, useEffect } from "react";
import "./styles/panel.css";

export interface Line {
	id?: number;
	lineNumber: number;
	content: string;
	file: {
		id?: number;
		name: string;
		path: string;
	};
};

interface File {
	content: Array<Content>;
	path: string;
};

interface Content {
	content: string;
	lineNumber: number;
};

interface Props {
	fields: Array<Line>,
	search: () => void,
	cleanAll: () => void
};

export const Panel = (props: Props): JSX.Element => {
	const { fields, search, cleanAll } = props;
	const [files, setFiles] = useState<File[]>([]);
	const [content, setContent] = useState<Content[]>([]);

	fields.forEach(({ content, file, lineNumber }) => {
		const { path } = file;
		const fileContent = { content: content, lineNumber };

		// Verifica se o arquivo já esta na lista de arquivos
		const sameFile = files.filter(item => item.path === path);
		if (!sameFile.length) {
			files.push({ content: [], path});
		}

		// Verifica se o conteúdo já foi preenchido
		const sameContent = sameFile.at(0)?.content.filter(item => item.lineNumber === lineNumber);
		if (!sameContent?.length) {
			files.filter(({path}) => path === file.path).at(0)?.content.push(fileContent);
		}
	});

	useEffect(() => {
		setFiles([]);
		setContent([]);
	}, [fields]);

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
							<p onClick={() => setContent(item.content)}>{item.path}</p>
						</div>
					))
				}
				</div>

				<span></span>
				
				<div className="panel" id="lines">
				{
					content.length > 0 &&
					content.map((item: Content, index: number) => (
						<div key={index}>
							<p>Linha {item.lineNumber}: {item.content}</p>
						</div>
					))
				}
				</div>
			</div>
		</>
	);
};
