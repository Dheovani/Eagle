import { useState, useEffect, useCallback } from "react";
import { GiBroom } from "react-icons/gi";
import { MdBrowserUpdated } from "react-icons/md";
import { GetMethod } from "@/utils/RestMethods";
import Tooltip from "@/components/Tooltip";
import Checkbox from "@/components/Checkbox";
import History, { PATH } from "@/components/History";
import Input from "@/components/Input";

export interface Path {
	path: string;
	id?: number;
}

const PathInput = (props: any): JSX.Element => {
	const {
		defaultValue,
		setSubFolders,
		updateDefaultValue
	} = props;

	const [paths, setPaths] = useState<Path[]>([]);
	const [selected, setSelected] = useState(false);

	const updateHistory = (): void => {
		GetMethod("http://localhost:8080/api/v1/Path", (status: number, response: any) => {
			if (status === 200) setPaths(response.results);
		});
	};

	useEffect(() => {
		updateHistory();
	}, []);

	const callPathSelector = (): void => {
		GetMethod("http://localhost:8080/api/v1/Path/select", (status: number, response: any) => {
			if (status === 200) {
				setPaths(response);
				updateDefaultValue(response);
			}
		});
	};

	const renderHistory = (): JSX.Element => {
		if (!paths?.length)
			return (<div></div>);

		return (
			<History
				items={paths}
				endpoint={PATH}
				updateDefaultValue={updateDefaultValue}
			/>
		);
	};

	const info = 'Este campo contém os repositórios aceitos na pesquisa. '
		+ 'Para selecionar múltiplos repositórios, utilize ";" e para '
		+ 'definir repositórios inválidos, utilize "!".';

	return (
		<>
			<h2>
				Caminhos aceitos
				{<Tooltip info={info} />}
			</h2>

			<div className="input-content">
				<Input
					id="path"
					placeholder="Exemplo: C:\\Users\\Example"
					defaultValue={defaultValue}
					selected={selected}
					setSelected={setSelected}
					onChange={(e) => {
						updateDefaultValue({
							path: e.target.value
						});
					}}
				/>

				<button className="select-button" onClick={callPathSelector}>
					<MdBrowserUpdated />
				</button>

				<button className="input-buttons" onClick={() => updateDefaultValue({ path: "" })}>
					<GiBroom />
				</button>

				<Checkbox id="subFolders" label="Considerar subdiretórios" onClick={setSubFolders} />
			</div>

			{selected && renderHistory()}
		</>
	);
};

export default PathInput;