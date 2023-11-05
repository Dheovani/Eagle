import { useState, useEffect } from "react";
import { GiBroom } from "react-icons/gi";
import { MdBrowserUpdated } from "react-icons/md";
import { GetMethod } from "../utils/RestMethods";
import { Tooltip } from "../utils/Tooltip";
import { History, PATH } from "./History";

export interface Path {
	path: string;
	id?: number;
}

export const PathInput = (props: any): JSX.Element => {
	const [selected, setSelected] = useState(false);
	const [paths, setPaths] = useState<Path[]>([]);

	const updateHistory = (): void => {
		GetMethod("http://localhost:8080/api/v1/Path", (status: number, response: any) => {
			if (status === 200) setPaths(response.results);
		});
	};

	useEffect(() => {
		updateHistory();
	}, [selected]);

	const callPathSelector = (): void => {
		GetMethod("http://localhost:8080/api/v1/Path/select", (status: number, response: any) => {
			if (status === 200) {
				setPaths(response);
				props.updateDefaultValue(response);
			}
		});
	};

	const renderHistory = (): JSX.Element => {
		if (!paths?.length) return <div></div>;

		return (
			<History
				items={paths}
				endpoint={PATH}
				updateDefaultValue={props.updateDefaultValue}
			/>
		);
	};

	const info =
		"Este campo contém os repositórios aceitos na pesquisa. " +
		'Para selecionar múltiplos repositórios, utilize ";" e para ' +
		'definir repositórios inválidos, utilize "!".';

	return (
		<>
			<h2>
				Caminhos aceitos
				{<Tooltip info={info} />}
			</h2>
			<div className="input-content">
				<input
					className="fields"
					type="text"
					name="path"
					id="path"
					value={props.defaultValue}
					placeholder={selected ? "" : "Exemplo: C:\\Users\\Example"}
					disabled={props.disable}
					onFocus={() => setSelected(true)}
					onBlur={() => setTimeout(() => setSelected(false), 100)}
					onChange={(e) => {
						const path = {
							path: e.target.value,
						};
						props.updateDefaultValue(path);
					}}
				/>

				<button disabled={props.disable} className="select-button" onClick={() => callPathSelector()}>
					<MdBrowserUpdated />
				</button>

				<button
					disabled={props.disable}
					className="input-buttons"
					onClick={() => props.updateDefaultValue({ path: "" })}>
					<GiBroom />
				</button>

				<label htmlFor="subFolders">Considerar subdiretórios</label>
				<input
					className="checkbox"
					type="checkbox"
					checked={props.checked}
					disabled={props.disable}
					onChange={() => {
						props.setSubFolders(!props.checked);
					}}
					name="subFolders"
					id="subFolders"
				/>
			</div>

			{selected && renderHistory()}
		</>
	);
};
